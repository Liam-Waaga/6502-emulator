/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#include "parcer.h"
#include "log/log.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

extern SYSTEM_FLAGS flags;

#define MAX_LINE_LENGTH 1024

/*--------------------------------------------------------------------
 * parse_uint
 *   Accepts decimal numbers that may contain underscores for readability.
 *   Stops parsing at the first '#' (comment) or any whitespace character.
 *   Returns -1 on any non‑digit character (other than '_' or allowed
 *   whitespace/comments) or if no digits are found.
 *-------------------------------------------------------------------*/
static int parse_uint(const char *s) {
    int num = 0;
    int found_digit = 0;

    while (*s) {
        if (*s == '#') break;               /* comment begins – stop */
        if (isspace((unsigned char)*s)) {   /* space / tab / newline – stop */
            break;
        }
        if (*s == '_') {
            s++;                            /* skip visual separators */
            continue;
        }
        if (isdigit((unsigned char)*s)) {
            found_digit = 1;
            num = num * 10 + (*s - '0');
            s++;
            continue;
        }
        return -1;                          /* invalid character */
    }

    return found_digit ? num : -1;          /* -1 if nothing parsed */
}

/*--------------------------------------------------------------------
 * parse_string
 *   Handles quoted ("...") and unquoted strings. Leading spaces and '='
 *   are skipped by the caller. For quoted strings, everything up to the
 *   closing quote is copied verbatim; for unquoted, copy until whitespace
 *   or comment. Caller must free the returned string.
 *-------------------------------------------------------------------*/
static char *parse_string(const char *s) {
    while (isspace((unsigned char)*s) || *s == '=') s++;

    if (*s == '"') {                       /* quoted string */
        s++;                                /* skip opening quote */
        const char *end = strchr(s, '"');
        if (!end) return NULL;              /* unterminated quote */
        size_t len = (size_t)(end - s);
        char *out = malloc(len + 1);
        if (!out) {
            log_error("Allocation failed in parse_string");
            exit(1);
        }
        memcpy(out, s, len);
        out[len] = '\0';
        return out;
    }

    /* unquoted */
    const char *end = s;
    while (*end && !isspace((unsigned char)*end) && *end != '#') end++;
    size_t len = (size_t)(end - s);
    char *out = malloc(len + 1);
    if (!out) {
        log_error("Allocation failed in parse_string");
        exit(1);
    }
    memcpy(out, s, len);
    out[len] = '\0';
    return out;
}

PARCER_DEVICE *parce_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        log_error("Cannot open config file: %s", path);
        exit(1);
    }

    PARCER_DEVICE *devices = NULL;
    size_t device_count = 0;
    PARCER_DEVICE current_device = {0};
    int in_device = 0;

    size_t line_number = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        /* Skip initial whitespace */
        char *trim = line;
        while (isspace((unsigned char)*trim)) trim++;

        /* Skip comments / empty lines */
        if (*trim == '#' || *trim == '\0' || *trim == '\n') continue;

        /* Section headers */
        if (*trim == '[') {
            /* If we were inside a device section, flush the device */
            if (in_device) {
                devices = realloc(devices, sizeof(PARCER_DEVICE) * (device_count + 1));
                if (!devices) {
                    log_error("realloc failed while adding device");
                    exit(1);
                }
                devices[device_count++] = current_device;
                memset(&current_device, 0, sizeof(PARCER_DEVICE));
            }

            if (strncmp(trim, "[ram]", 5) == 0) {
                current_device.type = DEV_RAM;
                in_device = 1;
            } else if (strncmp(trim, "[rom]", 5) == 0) {
                current_device.type = DEV_ROM;
                in_device = 1;
            } else {
                in_device = 0; /* system or unknown – handled outside devices */
            }
            continue;
        }

        /* Key‑value parsing */
        char *eq = strchr(trim, '=');
        if (!eq) continue;                 /* malformed line */

        *eq = '\0';
        char *key = trim;
        char *val = eq + 1;

        /* Trim key */
        while (isspace((unsigned char)*key)) key++;
        char *key_end = key + strlen(key);
        while (key_end > key && isspace((unsigned char)*(key_end - 1))) *(--key_end) = '\0';

        while (isspace((unsigned char)*val)) val++;

        if (!in_device) {
            /* System‑wide options */
            if (strcmp(key, "loglevel") == 0) {
                LOGLEVEL level;
                char *level_buff = parse_string(val);

                if (strcmp(level_buff, "error")) {
                    level = LOG_ERROR;
                } else if (strcmp(level_buff, "warn")) {
                    level = LOG_WARN;
                } else if (strcmp(level_buff, "info")) {
                    level = LOG_INFO;
                } else {
                    log_error("Invalid value for loglevel \"%s\"", level_buff);
                    exit(1);
                }

                if (flags.loglevel == LOG_NONE) {
                    flags.loglevel = level;
                }
            } else if (strcmp(key, "clock_speed") == 0) {
                int speed = parse_uint(val);
                if (speed < 0) {
                    log_error("Invalid clock_speed value in %s", path);
                    exit(1);
                }
                flags.clock_speed = speed;
            }
            continue;
        }

        /* Device‑specific options */
        if (strcmp(key, "address_begin") == 0) {
            current_device.address_begin = parse_uint(val);
            if (current_device.address_begin > 65536) {
                log_error("Address End too large %d at %s:%d", current_device.address_begin, path, line_number);
                exit(1);
            }
        } else if (strcmp(key, "address_end") == 0) {
            current_device.address_end = parse_uint(val);
            if (current_device.address_end > 65536) {
                log_error("Address End too large %d at %s:%d", current_device.address_end, path, line_number);
                exit(1);
            }
        } else if (strcmp(key, "path") == 0 && current_device.type == DEV_ROM) {
            char *str = parse_string(val);
            if (!str || access(str, F_OK) != 0) {
                log_error("ROM file not found: %s", str ? str : val);
                exit(1);
            }
            current_device.dev_opts.rom_opts.path = str;
        }
    }

    /* Flush the final device if we were in one */
    if (in_device) {
        devices = realloc(devices, sizeof(PARCER_DEVICE) * (device_count + 1));
        if (!devices) {
            log_error("realloc failed while finalising devices");
            exit(1);
        }
        devices[device_count++] = current_device;
    }

    /* Mark the array end */
    if (device_count > 0) {
        devices[device_count - 1].isArrayEnd = 1;
    }

    fclose(file);
    return devices;
}

void free_parcer_dev_arr(PARCER_DEVICE *arr) {
    if (!arr) return;
    for (size_t i = 0;; i++) {
        if (arr[i].type == DEV_ROM) {
            free(arr[i].dev_opts.rom_opts.path);
        }
        if (arr[i].isArrayEnd) break;
    }
    free(arr);
}

void print_parcer_dev_arr(PARCER_DEVICE *arr) {
    for (size_t i = 0;; i++) {
        printf("DEV_TYPE = %d, Address_Begin = %ld, Address_End = %ld", arr[i].type, arr[i].address_begin, arr[i].address_end);
        if (arr[i].type == DEV_ROM) {
            printf(", Path = \"%s\"", arr[i].dev_opts.rom_opts.path);
        }
        printf("\n");
        if (arr[i].isArrayEnd) break;
    }
}

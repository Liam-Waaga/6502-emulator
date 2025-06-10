#include "parcer.h"
#include "log/log.h"
#include "types.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern RUNTIME_FLAGS flags;


struct SECTION_WITH_OPTS {
    int is_device;
    char const *section;
    int num_opts;
    char const **opts;
};


struct SECTION_OPTIONS {
    int section_count;
    struct SECTION_WITH_OPTS *sections;
};



void print_parcer_dev_arr(PARCER_DEVICE *arr) {
    for (size_t i = 0; !arr[i].isArrayEnd; i++) {
        printf("Name = \"%s\", DEV_TYPE = %d, Address_Begin = %d, Address_End = %d", arr[i].name, arr[i].type, arr[i].address_begin, arr[i].address_end);
        switch (arr[i].type) {
            case DEV_NONE:
                log_warn("Encountered device of type DEV_NONE in parcer device array, %s:%d", __FILE__, __LINE__);
                printf("\n");
                break;
            case DEV_ROM:
                printf(", Path = \"%s\"\n", arr[i].dev_opts.rom_opts.path);
                break;
            case DEV_RAM:
                printf("\n");
                break;
        }
    }
}



/* purely exists to stop compiler warnings */
void nothing(void) {
    return;
}


/* checks if str starts with prefix, then the next character is a ' ' or a '=' */
int str_starts_with_then_assignment(const char *str, const char *prefix) {
    size_t len_prefix = strlen(prefix);
    size_t len_str = strlen(str);
    int assignement_after_prefix = 0;
    for (size_t i = len_prefix; i < len_str; i++) {
        if (str[i] == '=') {
            assignement_after_prefix = 1;
        }
        if (str[i] != ' ' && str[i] != '\t') {
            break;
        }
    }
    return len_str >= len_prefix && strncmp(str, prefix, len_prefix) == 0 && assignement_after_prefix;
}



/* gets the option specified following the rules of my not-toml */
int get_option_from_buff(const char *buff, struct SECTION_WITH_OPTS section) {
    for (size_t i = 0; buff[i] == ' ' || buff[i] == '#' || buff[i] == '\n'; i++) {
        return -2;
    }
    for (int i = 0; i < section.num_opts; i++) {
        if (str_starts_with_then_assignment(buff, section.opts[i])) {
            return i;
        }
    }
    return -1;
}

/* give pointer to first character of the "uint" */
int get_uint_from_buff(const char *buff) {
    int num = 0;
                        
    for (size_t num_length = 0; num_length < strlen(buff); num_length++) {
        if (buff[num_length] < '0' || buff[num_length] > '9') {
            if (buff[num_length] == '#') break;
            if (buff[num_length] == '\n') break;
            if (buff[num_length] == ' ') break;
            if (buff[num_length] == '_') continue;
            return -1;
        }
        num *= 10;
        num += buff[num_length] - '0';
    }
    return num;
}

// char *get_string_from_buff(char const * buff) {
//     size_t string_len = 0;
//     int is_quoted = buff[0] == '"';
//     if (is_quoted) {
//         buff++;
//         int i = 0;
//         int is_escape;
//         while (1) {
//             if (buff[i] == '\\') {
//                 is_escape = !is_escape;
//             }
//             if (buff[i] == '"') {
//                 if (!is_escape) {

//                     break;
//                 }
//             }
//             if (is_escape) {
//                 switch (buff[i]) {
//                     case 'n':

//                 }
//             }
//             i++;
//             string_len++;
//         }
//     } else {
//         for (; buff[string_len] != ' ' && buff[string_len] != '\t' && buff[string_len] != '#'; string_len++ );
//         string_len++;
//     }

//     char *buffer = malloc(string_len + 1);
//     if (buffer == NULL) {
//         log_error("Allocation failed, %s:%d", __FILE__, __LINE__);
//         exit(1);
//     }
//     strncpy(buffer, buff, string_len);
//     buffer[string_len] = '\0';
//     return buffer;
// }


/* Parses a string with escapes, supports quoted and unquoted strings.
   Returns malloc'ed string with escapes processed.
   Caller must free. */
char *get_string_from_buff(const char *buff) {
    const char *p = buff;
    char *output;
    size_t out_capacity = 64;  // initial output buffer size
    size_t out_len = 0;

    output = malloc(out_capacity);
    if (!output) {
        fprintf(stderr, "Allocation failed\n");
        exit(1);
    }

    int is_quoted = (*p == '"');
    if (is_quoted) {
        p++;  // skip opening quote

        while (*p) {
            if (*p == '"') {
                // end of quoted string
                p++;
                break;
            }

            if (*p == '\\') {
                p++; // skip backslash
                if (*p == '\0') break; // premature end

                // Handle escaped newline (line continuation)
                if (*p == '\n' || *p == '\r') {
                    // skip all newline chars (handle \r\n)
                    if (*p == '\r' && *(p+1) == '\n') p++;
                    p++;
                    continue; // don't output anything for line continuation
                }

                switch (*p) {
                    case 'n': output[out_len++] = '\n'; break;
                    case 'r': output[out_len++] = '\r'; break;
                    case 't': output[out_len++] = '\t'; break;
                    case '\\': output[out_len++] = '\\'; break;
                    case '"': output[out_len++] = '"'; break;
                    case '0': output[out_len++] = '\0'; break;
                    // Add other escapes if needed
                    default:
                        // Unknown escape, copy literally (or handle error)
                        output[out_len++] = *p;
                        break;
                }
                p++;
            } else {
                output[out_len++] = *p++;
            }

            // Resize output buffer if needed
            if (out_len + 1 >= out_capacity) {
                out_capacity *= 2;
                char *tmp = realloc(output, out_capacity);
                if (!tmp) {
                    free(output);
                    fprintf(stderr, "Allocation failed\n");
                    exit(1);
                }
                output = tmp;
            }
        }
    } else {
        // unquoted string, ends at space, tab, or '#'
        while (*p && *p != ' ' && *p != '\t' && *p != '#') {
            // copy literally, no escapes in unquoted strings by default
            output[out_len++] = *p++;

            if (out_len + 1 >= out_capacity) {
                out_capacity *= 2;
                char *tmp = realloc(output, out_capacity);
                if (!tmp) {
                    free(output);
                    fprintf(stderr, "Allocation failed\n");
                    exit(1);
                }
                output = tmp;
            }
        }
    }

    output[out_len] = '\0';
    return output;
}

PARCER_DEVICE *parce_file(const char *path) {
    FILE *config = fopen(path, "r");
    if (config == NULL) {
        log_error("Open file error, file path \"%s\"", path);
        exit(1);
    };

    
    struct SECTION_OPTIONS section_options = {
        .section_count = 3,
    };
    section_options.sections = malloc(sizeof(struct SECTION_WITH_OPTS) * section_options.section_count);
    section_options.sections[0] = (struct SECTION_WITH_OPTS) {
        .is_device = 0,
        .section = "system",
        .num_opts = 2,
        .opts = (char const *[]) {
            "clock_speed",
            "loglevel"
        }
    };
    section_options.sections[1] = (struct SECTION_WITH_OPTS) {
        .is_device = 1,
        .section = "ram",
        .num_opts = 2,
        .opts = (char const *[]) {
            "address_begin",
            "address_end"
        }
    };
    section_options.sections[2] = (struct SECTION_WITH_OPTS) {
        .is_device = 1,
        .section = "rom",
        .num_opts = 2,
        .opts = (char const *[]) {
            "address_begin",
            "address_end",
            "path"
        }
    };

    /* other options */
    PARCER_DEVICE *dev_settings_arr = malloc(sizeof(PARCER_DEVICE));
    size_t dev_arr_used = 0;
    size_t dev_arr_allocated = 1;
    PARCER_DEVICE device;
    memset(&device, 0, sizeof(PARCER_DEVICE));

    if (dev_settings_arr == NULL) {
        log_error("Allocation error, %s:%d", __FILE__, __LINE__);
        exit(1);
    }

    char buff[1024];
    int section_specifier = -1;
    int option_specifier = -1;

    size_t line = 0;

    int is_making_device = 0;

    while (fgets(buff, sizeof(buff), config)) {
        line++;
        if (!strchr(buff, '\n') && !feof(config))
            log_error("Line %d is too long in \"%s\"", line, path);
        if (buff[0] == '[') {
            for (int i = 0; i < section_options.section_count; i++) {
                if (strncmp(buff + 1, section_options.sections[i].section, strlen(section_options.sections[i].section)) == 0) {
                    section_specifier = i;
                    goto LOOP_END;
                }
            }
            if (is_making_device == 1) {
                if (dev_arr_used == dev_arr_allocated) {
                    PARCER_DEVICE *tmp = realloc(dev_settings_arr, sizeof(PARCER_DEVICE) * (dev_arr_allocated *= 2));
                    if (tmp == NULL) {
                        log_error("realloc fail at %s:%d", __FILE__, __LINE__);
                        exit(1);
                    }
                    dev_settings_arr = tmp;
                }
                device.isArrayEnd = 0;
                dev_settings_arr[dev_arr_used++] = device;
            }
        }
        
        if (section_specifier >= section_options.section_count) {
            log_error("Section specifier refers to section that does not exist, %s:%d, %s:%d", path, line, __FILE__, __LINE__);
            exit(1);
        }

        option_specifier = get_option_from_buff(buff, section_options.sections[section_specifier]);

        if (option_specifier == -1) {
            log_error("Unknown option at %s:%d", path, line);
            exit(1);
        }
        if (option_specifier == -2) {
            goto LOOP_END;
        }

        char *value_position = (char *) buff + strlen(section_options.sections[section_specifier].opts[option_specifier]) + 1;
        for (; *value_position == ' ' || *value_position == '=' || *value_position == '\t'; value_position++);
        
        switch (section_specifier) {

            case 0: {
                is_making_device = section_options.sections[0].is_device; /* system settings */



                switch (option_specifier) {
                    case 0: /* clock_speed */
                        nothing();
                        int num = get_uint_from_buff(value_position);
                        if (num == -1) {
                            log_error("Invalid value for clock speed at line %d", line);
                            exit(1);
                        }
                        flags.clock_speed = num;
                        break;
                    case 1: /* loglevel */
                        nothing();
                        int log_level = get_uint_from_buff(value_position);
                        if (log_level > 2 || log_level < 0) {
                            log_error("Invalid value for loglevel at %s:%d, 0 for error, 1 for warn, 2 for info", path, line);
                            exit(1);
                        }
                        flags.loglevel = log_level;
                        break;
                }
                break;
            }
            case 1: {
                is_making_device = section_options.sections[1].is_device; /* ram is a device, unlike system settings */

                device.type = DEV_RAM;

                switch (option_specifier) {
                    int num;
                    case 0: /* address_begin */
                        nothing();
                        num = get_uint_from_buff(value_position);
                        if (num == -1) {
                            log_error("Invalid value for address_begin at %s:%d", path, line);
                            exit(1);
                        }
                        device.address_begin = num;
                        break;
                    case 1: /* address_end */
                        nothing();
                        num = get_uint_from_buff(value_position);
                        if (num == -1) {
                            log_error("Invalid value for address_end at %s:%d", path, line);
                            exit(1);
                        }
                        device.address_end = num;
                        break;

                }
                break;
            }
            case 2: {
                device.type = DEV_ROM;

                log_error("Unimplemented, %s:%d, %s:%d", path, line, __FILE__, __LINE__);
                exit(1);
                break;
            }
        }

        LOOP_END:
        nothing();
    }

    dev_settings_arr[dev_arr_used].isArrayEnd = 1;
    
    return dev_settings_arr;
}

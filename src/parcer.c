#include "parcer.h"
#include "log/log.h"
#include "types.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern RUNTIME_FLAGS flags;

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
int get_option_from_buff(const char *buff, char const * const opt_array[] /* last element = NULL */) {
    for (size_t i = 0; opt_array[i] != NULL; i++) {
        if (str_starts_with_then_assignment(buff, opt_array[i])) {
            return i;
        }
    }
    return -1;
}


int get_uint_from_buff(const char *buff) {
    int num = 0;
                        
    for (size_t num_length = 0; buff[num] != '#' && buff[num] != '\n'; num_length++) {
        if (buff[num] < 48 || buff[num] > 57) {
            return -1;
        }
        num *= 10;
        num += buff[num_length] - '0';
    }
    return num;
}


PARCER_DEVICE *parce_file(const char *path) {
    FILE *config = fopen(path, "r");
    if (config == NULL) {
        log_error("Open file error, file path \"%s\"", path);
        exit(1);
    };

    
    int dev_count = 0;

    char const * const section_specifiers[] = {
        "[system]\n",
        "[ram]\n",
        "[rom]\n",
        NULL,
    };

    char const * const system_opts[] = {
        "clock_speed",
        "loglevel",
        NULL,
    };

    char const * const ram_opts[] = {
        "address_begin",
        "address_end",
        NULL
    };

    char const * const rom_opts[] = {
        "address_begin",
        "address_end",
        "path",
        NULL
    };

    /* other options */

    DEV_TYPE type;

    PARCER_DEVICE *dev_settings_arr = malloc(sizeof(PARCER_DEVICE));
    PARCER_DEVICE dev;
    if (dev_settings_arr == NULL) {
        log_error("Allocation error, %s:%d", __FILE__, __LINE__);
        exit(1);
    }
    size_t arr_length = 1;


    char buff[1024];
    int section_specifier = -1;
    int option_specifier = -1;

    size_t line = 0;

    while (fgets(buff, sizeof(buff), config)) {
        if (!strchr(buff, '\n') && !feof(config))
            log_error("Line %d is too long in \"%s\"", line, path);

        line++;
        for (int i = 0; section_specifiers[i] != NULL; i++) {
            if (strcmp(section_specifiers[i], buff) == 0) {
                section_specifier = i;
                goto LOOP_END;
            }
        }
        switch (section_specifier) {
            case 0:
                option_specifier = get_option_from_buff(buff, system_opts);

                if (option_specifier == -1) {
                    log_error("Unkown option at line %s:%d", path, line);
                    exit(1);
                }

                char *value_position = (char *) buff + strlen(system_opts[0]) + 1;
                for (; *value_position == ' ' || *value_position == '='; value_position++);

                switch (option_specifier) {
                    case 0:
                        nothing();
                        int num = get_uint_from_buff(value_position);
                        if (num == -1) {
                            log_error("Invalid value for clock speed at %d", line);
                            exit(1);
                        }
                        flags.clock_speed = num;
                        break;
                    case 1:
                        if (*value_position != '0' && *value_position != '1' && *value_position != '2') {
                            log_error("Invalid value for loglevel at %s:%d, 0 for error, 1 for warn, 2 for info", path, line);
                            exit(1);
                        }
                        flags.loglevel = *value_position - '0';
                }
                break;
            case 1:
                option_specifier = get_option_from_buff(buff, ram_opts);
                
                if (option_specifier == -1) {
                    log_error("Unkown option at line %s:%d", path, line);
                    exit(1);
                }

                switch (option_specifier) {
                    case 0:
                        log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
                }
        }

        LOOP_END:
        nothing();
    }
    
    return dev_settings_arr;
}

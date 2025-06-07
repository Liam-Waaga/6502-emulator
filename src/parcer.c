#include "parcer.h"
#include "log/log.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

PARCER_DEVICE *parce_file(const char *path) {
    int config_fd = open(path, O_RDONLY);
    if (config_fd < 0) {
        log_error("Open file error, file path \"%s\"", path);
        exit(1);
    }

    struct stat file_stat;
    int file_size_bytes;
    if (fstat(config_fd, &file_stat) != 0) {
        log_error("Unable to get file status to file \"%s\", %s:%d", path, __FILE__, __LINE__);
        exit(1);
    }
    file_size_bytes = file_stat.st_size;

    char *buff = (char *) malloc(file_size_bytes);
    
    read(config_fd, buff, file_size_bytes);
    int dev_count = 0;

    char const * const section_specifiers[] = {
        "device",
        "system",
        NULL
    };

    PARCER_DEVICE *dev_settings_arr = malloc(sizeof(PARCER_DEVICE));

    int line_number = 1;
    int col_number = 1;

    int is_comment = 0;
    int is_section_specifier = 0;
    int section_specifier = -1;
    for (int i = 0; i < file_size_bytes; i++) {
        if (buff[i] == '\n') {
            line_number++;
            col_number = 1;
        } else {
            col_number++;
        }
        if (is_comment) {
            is_comment = !(buff[i] == '\n');
            continue;
        }
        if (buff[i] == '#') is_comment = 1;

        if (buff[i] == '[') {
            is_section_specifier = 1;
            continue;
        }
        if (is_section_specifier) {
            for (section_specifier = 0; section_specifiers[section_specifier] != NULL; section_specifier++) {
                for (int k = 0; section_specifiers[section_specifier][k] != '\0'; k++) {
                    if (buff[i++] != section_specifiers[section_specifier][k]) {
                        if (section_specifiers[section_specifier + 1] == NULL) {
                            log_error("Unkown section specifier found in file \"%s\" at %d:%d", path, line_number, col_number);
                            exit(1);
                        }
                        break;
                    }
                }
            }
            if (buff[++i] != ']')
                log_error("Expected ']' in file \"%s\" at %d:%d", path, line_number, col_number);
            exit(1);
        }
        /* TODO, SETUP PARCER DEVICE STRUCT ARRAY */        
    }
}
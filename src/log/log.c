/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


#include "log.h"
#include "../types.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

extern SYSTEM_FLAGS flags;



void log_info(const char *message, ...) {
    
    if (flags.loglevel < LOG_INFO) {
        return;
    }

    va_list args;
    va_start(args, message);
    
    char time_format[256];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(time_format, 256, "%m-%d %H:%M:%S", tm_info);



    fprintf(stderr, "[INFO] %s: ", time_format);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
}


void log_warn(const char *message, ...) {
    if (flags.loglevel < LOG_WARN) {
        return;
    }

    va_list args;
    va_start(args, message);
    
    char time_format[256];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(time_format, 256, "%m-%d %H:%M:%S", tm_info);



    fprintf(stderr, "[WARN] %s: ", time_format);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
}

void log_error(const char *message, ...) {
    
    if (flags.loglevel < LOG_ERROR) {
        return;
    }

    va_list args;
    va_start(args, message);
    
    char time_format[256];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(time_format, 256, "%m-%d %H:%M:%S", tm_info);



    fprintf(stderr, "[ERROR] %s: ", time_format);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
}

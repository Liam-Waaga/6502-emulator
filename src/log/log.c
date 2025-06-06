
#include "log.h"

#include <stdio.h>
#include <time.h>



void log_info(const char *message) {
    const char format[256];
    time_t now = time();
    struct tm *tm_info = localtime(&now);

    strftime(format, 256, "%m-%d %H:%M:%S: ", tm_info);

    printf("[INFO] %s:%d %s%s", __FILE__, __LINE__, format, message);
}


void log_warn(const char *message) {
    const char format[256];
    time_t now = time();
    struct tm *tm_info = localtime(&now);

    strftime(format, 256, "%m-%d %H:%M:%S: ", tm_info);

    printf("[WARN] %s:%d %s%s", __FILE__, __LINE__, format, message);
}


void log_error(const char *message) {
    const char format[256];
    time_t now = time();
    struct tm *tm_info = localtime(&now);

    strftime(format, 256, "%m-%d %H:%M:%S: ", tm_info);

    printf("[ERROR] %s:%d %s%s", __FILE__, __LINE__, format, message);
}
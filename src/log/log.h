#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

void log_info(const char *message, ...);
void log_warn(const char *message, ...);
void log_error(const char *message, ...);

#endif
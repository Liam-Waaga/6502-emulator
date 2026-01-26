
#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static LOGLEVEL _loglevel = INFO;

void set_loglevel(LOGLEVEL level) {
    _loglevel = level;
}

void _log(char const * file, int linenumber, char const * const function, LOGLEVEL level, char const * const format, ...) {
    if (level < _loglevel) return;

    va_list args;
    va_start(args, format);

    char const * tmp = strstr(file, "/src/");
    if (tmp) file = tmp + 1;

    fprintf(stderr, "%s:%s:%d ", file, function, linenumber);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    fflush(stderr);
}


#include "log.h"

#include <stdarg.h>
#include <stdio.h>


static LOGLEVEL _loglevel = INFO;

void set_loglevel(LOGLEVEL level) {
    _loglevel = level;
}

void _log(char const * const file, int linenumber, char const * const function, LOGLEVEL level, char const * const format, ...) {
    if (level < _loglevel) return;

    va_list args;
    va_start(args, format);

    fprintf(stderr, "%s:%d in function %s: ", file, linenumber, function);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    fflush(stderr);
}
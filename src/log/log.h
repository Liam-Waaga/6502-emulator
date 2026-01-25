
#ifndef LOG_H
#define LOG_H


/* this is the log macro. use it like this `log(ERROR, "failed to malloc array at address %d", somearr);`*/
#define log(loglevel, format, ...) _log(__FILE__, __LINE__, __func__, loglevel, format, __VA_ARGS__)

typedef enum {
    INFO,
    WARN,
    ERROR,
} LOGLEVEL;

void set_loglevel(LOGLEVEL level);


/* internal function for logging, not meant to be used by anything except through the macro */
void _log(char const * const file, int linenumber, char const * const function, LOGLEVEL level, char const * const format, ...);


#endif
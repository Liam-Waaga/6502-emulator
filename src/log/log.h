
#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif


/* this is the log macro. use it like this `logf(ERROR, "failed to malloc array at address %d", somearr);`*/
#define logf(loglevel, format, ...) _log(__FILE__, __LINE__, __func__, loglevel, format, __VA_ARGS__)
#define log(loglevel, format) _log(__FILE__, __LINE__, __PRETTY_FUNCTION__, loglevel, format)

typedef enum {
    INFO,
    WARN,
    ERROR,
} LOGLEVEL;

void set_loglevel(LOGLEVEL level);


/* internal function for logging, not meant to be used by anything except through the macro */
void _log(char const * const file, int linenumber, char const * const function, LOGLEVEL level, char const * const format, ...);

#ifdef __cplusplus
}
#endif

#endif

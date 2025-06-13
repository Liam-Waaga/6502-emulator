#ifndef TYPES_H
#define TYPES_H

#if __WIN32
#error Win32 not supported, remove once I decide that the win32 api is worth the pain
#endif



#include <stdint.h>
#include <stddef.h>

typedef uint8_t Byte_t;
typedef uint16_t Word_t;
typedef int8_t Byte_signed_t;
typedef int16_t Word_signed_t;

typedef struct {
    unsigned long clock_speed; /* 0 for system clock */
    int loglevel; /* 0 for error, 1 for warn, 2 for info */
} SYSTEM_FLAGS;

typedef enum {
    DEV_NONE,
    DEV_ROM,
    DEV_RAM,
} DEV_TYPE;


#endif
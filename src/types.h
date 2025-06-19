/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


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

typedef enum {
    LOG_NONE = 0,
    LOG_QUIET = 1,
    LOG_ERROR = 2,
    LOG_WARN = 3,
    LOG_INFO = 4,
} LOGLEVEL;

typedef struct {
    unsigned long clock_speed; /* 0 for system clock */
    LOGLEVEL loglevel;
} SYSTEM_FLAGS;

typedef enum {
    DEV_NONE = 0,
    DEV_ROM = 1,
    DEV_RAM = 2,
} DEV_TYPE;


#endif

/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
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

typedef struct {
    unsigned long clock_speed; /* 0 for system clock */
    int loglevel; /* 0 for error, 1 for warn, 2 for info */
} SYSTEM_FLAGS;

typedef enum {
    DEV_NONE = 0,
    DEV_ROM = 1,
    DEV_RAM = 2,
} DEV_TYPE;


#endif

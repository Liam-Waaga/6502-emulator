#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t Byte_t;
typedef uint16_t Word_t;

typedef struct {
    int ram_size; /* in bytes */
    int rom_size;
    int loglevel; /* 0 for error, 1 for warn, 2 for info */
} RUNTIME_FLAGS;


#endif
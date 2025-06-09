#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t Byte_t;
typedef uint16_t Word_t;

typedef struct {
    unsigned long clock_speed; /* 0 for system clock */
    int loglevel; /* 0 for error, 1 for warn, 2 for info */
} RUNTIME_FLAGS;

typedef enum {
    DEV_ROM,
    DEV_RAM,
} DEV_TYPE;


#endif
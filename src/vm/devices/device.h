

#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"

/* Any device type which is accessed through the 6502 memory must include this as the first struct member. This allows us to just cast to a Device struct
 * You should always use the initialization functions provided below. */
typedef struct {
    Word _begin_address;
    Word _end_address;
    Byte (*_read_byte)(void *self, Word address);
    void (*_write_byte)(void *self, Word address, Byte value);
    void (*_cleanup)(void * self);
} Device;


#endif
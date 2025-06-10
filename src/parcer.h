#ifndef PARCER_H
#define PARCER_H

#include "types.h"
#include "devices/ram.h"
#include "devices/rom.h"

/* used as part of an array */
typedef struct {
    DEV_TYPE type;
    Word_t address_begin;
    Word_t address_end;
    union {
        struct ROM_OPTS rom_opts;
        
    } dev_opts;
    int isArrayEnd;
} PARCER_DEVICE;

PARCER_DEVICE *parce_file(const char *path);

void free_parcer_dev_arr(PARCER_DEVICE *arr);

void print_parcer_dev_arr(PARCER_DEVICE *arr);

#endif
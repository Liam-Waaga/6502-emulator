#ifndef PARCER_H
#define PARCER_H

#include "mem.h"
#include "types.h"

struct ROM_OPTS {
    char *path;
};

/* used as part of an array */
typedef struct {
    char *name;
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

#endif
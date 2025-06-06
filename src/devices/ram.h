#ifndef RAM_H
#define RAM_H
#include "../types.h"

#include <stddef.h>


typedef struct {
    void *memory;
    size_t size; /* size in bytes */
} RAM;

RAM *ram_init();
void ram_deinit(RAM *ram);

#endif

#include "../types.h"

#include <stddef.h>


typedef struct {
    void *memory;
    size_t size; /* size in bytes */
} RAM;

RAM *ram_init(struct RUNTIME_FLAGS *flags);
void ram_deinit(RAM *ram);

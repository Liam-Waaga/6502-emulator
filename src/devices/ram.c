#include "ram.h"

#include <stdlib.h>

RAM *ram_init(struct RUNTIME_FLAGS *flags) {
    RAM *ram = malloc(sizeof(RAM));
    ram->memory = malloc(flags->ram_size);
    ram->size = flags->ram_size;
    return ram;
}
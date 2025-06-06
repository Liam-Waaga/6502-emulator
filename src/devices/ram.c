#include "ram.h"

#include <stdlib.h>

extern RUNTIME_FLAGS flags;

RAM *ram_init() {
    RAM *ram = malloc(sizeof(RAM));
    ram->memory = malloc(flags.ram_size);
    ram->size = flags.ram_size;
    return ram;
}
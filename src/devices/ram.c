#include "ram.h"

#include <stdlib.h>

extern RUNTIME_FLAGS flags;

RAM *ram_init() {
    RAM *ram = malloc(sizeof(RAM));
    ram->memory = (Byte_t *) malloc(flags.ram_size);
    ram->size = flags.ram_size;
    return ram;
}


void ram_deinit(RAM *ram) {
    free(ram->memory);
    free(ram);
}

Word_t ram_read_word(RAM *ram, Word_t address) {
    if (address + 1 > ram->size) {
        log_error("attempted to access ram memory at address %d with ram size %d, %s:%d", address, ram->size, __FILE__, __LINE__);
        exit(1);
    }
    return (Word_t) *(ram->memory + address) | *(ram->memory + address + 1) << 8;
}
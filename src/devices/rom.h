#ifndef ROM_H
#define ROM_H
#include "../types.h"

#include <stddef.h>


typedef struct {
    int fd; /* file on disc */
    Byte_t *data;
    size_t size;
} ROM;


ROM *rom_init(const char *path);

void rom_deinit(ROM *rom);

Word_t rom_read_word(ROM *rom, Word_t address);
Byte_t rom_read_byte(ROM *rom, Word_t address);

#endif
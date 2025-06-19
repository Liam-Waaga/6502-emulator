/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


#include "ram.h"
#include "log.h"
#include "types.h"

#include <stdlib.h>
#include <unistd.h>

extern SYSTEM_FLAGS flags;

RAM *ram_init(int size) {
    RAM *ram = malloc(sizeof(RAM));
    ram->memory = (Byte_t *) malloc(size);
    ram->size = size;
    return ram;
}


void ram_deinit(RAM *ram) {
    free(ram->memory);
    free(ram);
}

Word_t ram_read_word(RAM *ram, Word_t address) {
    if ((size_t)address + 1 >= ram->size) {
        log_error("attempted to access ram memory at address %d with ram size %d, %s:%d", address, ram->size, __FILE__, __LINE__);
        exit(1);
    }
    return (Word_t) *(ram->memory + address) | (*(ram->memory + address + 1) << 8);
}

Byte_t ram_read_byte(RAM *ram, Word_t address) {
    if (address >= ram->size) {
        log_error("Attempted to access ram memory at address %d with ram size %d, %s:%d", address, ram->size, __FILE__, __LINE__);
        exit(1);
    }
    return *(ram->memory + address);
}

void ram_write_word(RAM *ram, Word_t address, Word_t value) {
    if ((size_t)address + 1 >= ram->size) {
        log_error("Attempted to write to address %d with ram size %d, %s:%d", address, ram->size, __FILE__, __LINE__);
        exit(1);
    }
    *((Word_t *) (ram->memory + address)) = value;
}


void ram_write_byte(RAM *ram, Word_t address, Byte_t value) {
    if (address >= ram->size) {
        log_error("Attempted to write to address %d with ram size %d, %s:%d", address, ram->size, __FILE__, __LINE__);
        exit(1);
    }
    *(ram->memory + address) = value;
}

/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#ifndef RAM_H
#define RAM_H
#include "../types.h"

#include <stddef.h>


typedef struct {
    Byte_t *memory;
    size_t size; /* size in bytes */
} RAM;

RAM *ram_init(int size);
void ram_deinit(RAM *ram);

Word_t ram_read_word(RAM *ram, Word_t address);
Byte_t ram_read_byte(RAM *ram, Word_t address);

void ram_write_word(RAM *ram, Word_t address, Word_t value);
void ram_write_byte(RAM *ram, Word_t address, Byte_t value);

#endif

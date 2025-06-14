/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#ifndef ROM_H
#define ROM_H
#include "../types.h"

#include <stddef.h>

struct ROM_OPTS {
    char *path;
};

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
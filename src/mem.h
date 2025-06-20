/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


#ifndef MEM_H
#define MEM_H

#include "parcer.h"
#include "types.h"
#include "devices/ram.h"
#include "devices/rom.h"

#include <stddef.h>

/* Struct that can contain a device */
typedef struct {
    union {
        /* add more devices as they are implemented */
        RAM *ram;
        ROM *rom;
    } device;
    size_t address_begin;
    size_t address_end; /* not inclusive */
    DEV_TYPE type;
} DEVICE;


typedef struct {
    DEVICE *devices;
    size_t dev_count;
    size_t dev_allocated;
} ADDR_SPACE;


ADDR_SPACE *addr_init(PARCER_DEVICE *device_arr);
void addr_deinit(ADDR_SPACE *address_space);

void vm_register_device(ADDR_SPACE *address_space, DEVICE dev);

void device_deinit(DEVICE device);

Byte_t vm_read_byte(ADDR_SPACE *vm, Word_t address);
Word_t vm_read_word(ADDR_SPACE *vm, Word_t address);

void vm_write_byte(ADDR_SPACE *vm, Word_t address, Byte_t value);
void vm_write_word(ADDR_SPACE *vm, Word_t address, Word_t value);



#endif

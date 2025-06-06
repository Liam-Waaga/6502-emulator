#ifndef MEM_H
#define MEM_H

#include "types.h"
#include "devices/ram.h"
#include "devices/rom.h"
#include <stddef.h>

#define DEV_MEM 0
#define DEV_ROM 1

/* Struct that can contain a device */
typedef struct {
    union {
        /* add more devices as they are implemented */
        RAM *ram;
        ROM *rom;
    } device;
    Word_t address_begin;
    Word_t address_end; /* not inclusive, if you access address end, and anothers address begin is 
                           the same value, it accesses the other device */
    int type;
} DEVICE;


typedef struct {
    DEVICE *devices;
    size_t dev_count;
    size_t dev_alloced;
} ADDR_SPACE;


ADDR_SPACE *addr_init();

void vm_register_device(ADDR_SPACE *address_space, DEVICE dev);


Byte_t vm_read_byte(Word_t address);
Word_t vm_read_word(Word_t address);

Byte_t vm_write_byte(Word_t address);
Word_t vm_write_word(Word_t address);



#endif
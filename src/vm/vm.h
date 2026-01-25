

#ifndef VM_H
#define VM_H

#include "common.h"
#include "device.h"

typedef struct {
    /* array of pointers to a single device, because each device must be malloced individually, because device is a generic struct */
    Device ** devices;
} VM;

VM * vm_init();
VM * vm_cleanup();
VM * vm_add_device(Device *dev);

Byte vm_read_byte(VM address_space, Word address);
Word vm_read_word(VM address_space, Word address);

void vm_write_byte(VM address_space, Word address, Byte value);
void vm_write_word(VM address_space, Word address, Word value);


#endif
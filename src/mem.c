#include "mem.h"
#include <stdlib.h>

ADDR_SPACE *addr_init(struct RUNTIME_FLAGS run_flags) {
    ADDR_SPACE *addr_space = malloc(sizeof(ADDR_SPACE));
    addr_space->devices = NULL;
    addr_space->dev_count = 0;
    addr_space->dev_alloced = 0;
    // TODO, add to device array
    DEVICE ram;
    ram.device.ram = ram_init(run_flags);
    ram.address_begin = 0;
    ram.address_end = run_flags.ram_size - 1;

    vm_register_device(addr_space, ram);

    return addr_space;
}

void vm_register_device(ADDR_SPACE *address_space, DEVICE device) {
    
    if (address_space->dev_alloced == address_space->dev_count) {

        address_space->dev_alloced *= 2;
        if (address_space->dev_alloced == 0) {
            address_space->dev_alloced = 1;
        }

        DEVICE *new_device = realloc(address_space->devices, sizeof(DEVICE) * address_space->dev_alloced);
        if (new_device == NULL) {
            /* handle realloc failure */
        } else {
            address_space->devices = new_device;
        }
    }

    address_space->devices[address_space->dev_count] = device;
}
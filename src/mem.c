#include "mem.h"
#include "devices/ram.h"
#include "log/log.h"
#include "types.h"

#include <stddef.h>
#include <stdlib.h>

extern RUNTIME_FLAGS flags;

ADDR_SPACE *addr_init() {
    ADDR_SPACE *addr_space = (ADDR_SPACE *) malloc(sizeof(ADDR_SPACE));
    addr_space->devices = NULL;
    addr_space->dev_count = 0;
    addr_space->dev_allocated = 0;

    DEVICE ram;
    ram.device.ram = ram_init();
    ram.type = DEV_RAM;
    ram.address_begin = 0;
    ram.address_end = flags.ram_size - 1;

    vm_register_device(addr_space, ram);
    /* TODO, register ROM once rom is implemented */

    return addr_space;
}

void vm_register_device(ADDR_SPACE *address_space, DEVICE device) {
    
    if (address_space->dev_allocated == address_space->dev_count) {

        address_space->dev_allocated *= 2;
        if (address_space->dev_allocated == 0) {
            address_space->dev_allocated = 1;
        }
        
        DEVICE *new_device = (DEVICE *) realloc(address_space->devices, sizeof(DEVICE) * address_space->dev_allocated);
        if (new_device == NULL) {
            /* handle realloc failure */
            log_error("Realloc failure while extending device array in \"%s:%d\"", __FILE__, __LINE__);
            exit(1);
        } else {
            address_space->devices = new_device;
        }
    }
    address_space->devices[address_space->dev_count] = device;
    log_info("Registered device");
}


void device_deinit(DEVICE device) {
    switch (device.type) {
        case DEV_RAM:
            ram_deinit(device.device.ram);
            break;
        case DEV_ROM:
            rom_deinit(device.device.rom);
            break;
    }
}


void addr_deinit(ADDR_SPACE *address_space) {
    for (size_t i = 0; i < address_space->dev_count; i++) {
        device_deinit(address_space->devices[i]);
    }
}


Word_t vm_read_word(ADDR_SPACE *vm, Word_t address) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}

Byte_t vm_read_byte(ADDR_SPACE *vm, Word_t address) {
    DEVICE *dev = NULL;
    for (size_t i = 0; i < vm->dev_count; i++) {
        if (address >= vm->devices[i].address_begin &&
            address < vm->devices[i].address_end) {
            dev = &vm->devices[i];
        }
    }

    if (dev == NULL) {
        log_error("Tried to access memory address %d, but found no device asscodiated with it", address);
        exit(1);        
    }

    switch (dev->type) {
        case DEV_ROM:
            return rom_read_byte(dev->device.rom, address - dev->address_begin);
            break;
        case DEV_RAM:
            return ram_read_byte(dev->device.ram, address - dev->address_begin);
            break;
        default: 
            log_error("Device accessed of unknown type (%d)", dev->type);
            break;
    }


}

void vm_write_byte(ADDR_SPACE *vm, Word_t address, Byte_t value) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void vm_write_word(ADDR_SPACE *vm, Word_t address, Word_t value) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}

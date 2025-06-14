/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#include "mem.h"
#include "clock.h"
#include "devices/ram.h"
#include "devices/rom.h"
#include "log/log.h"
#include "parcer.h"
#include "types.h"

#include <stddef.h>
#include <stdlib.h>

extern SYSTEM_FLAGS flags;

ADDR_SPACE *addr_init(PARCER_DEVICE *device_arr) {
    ADDR_SPACE *addr_space = (ADDR_SPACE *) malloc(sizeof(ADDR_SPACE));
    addr_space->devices = malloc(sizeof(DEVICE));
    addr_space->dev_count = 0;
    addr_space->dev_allocated = 1;

    for (size_t i = 0; !device_arr[i].isArrayEnd; i++) {
        DEVICE dev;
        dev.address_begin = device_arr[i].address_begin;
        dev.address_end = device_arr[i].address_end;
        dev.type = device_arr[i].type;

        switch (dev.type) {
            case DEV_NONE:
                log_warn("Encountered DEV_NONE, ignoring");
                break;
            case DEV_ROM:
                dev.device.rom = rom_init(device_arr[i].dev_opts.rom_opts.path);
                break;
            case DEV_RAM:
                dev.device.ram = ram_init(dev.address_end - dev.address_begin);
                break;
        }
        if (addr_space->dev_allocated == addr_space->dev_count) {
            DEVICE *tmp = (DEVICE *) realloc(addr_space->devices, addr_space->dev_allocated *= 2);
            if (tmp == NULL) {
                log_error("realloc failure at %s:%d", __FILE__, __LINE__);
                exit(1);
            }
            addr_space->devices = tmp;
        }
        addr_space->devices[addr_space->dev_count++] = dev;
    }

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
        case DEV_NONE: {
            log_warn("Can't deinit device of type DEV_NONE, %s:%d", __FILE__, __LINE__);
            break;
        }
        case DEV_RAM: {
            ram_deinit(device.device.ram);
            device.device.ram = NULL;
            break;
        }
        case DEV_ROM: {
            rom_deinit(device.device.rom);
            device.device.rom = NULL;
            break;
        }
        default: {
            log_warn("Can't deinit device of unkown type");
            break;
        }
    }
}


void addr_deinit(ADDR_SPACE *address_space) {
    for (size_t i = 0; i < address_space->dev_count; i++) {
        device_deinit(address_space->devices[i]);
    }
}


Word_t vm_read_word(ADDR_SPACE *vm, Word_t address) {
    return (Word_t) vm_read_byte(vm, address) | (vm_read_byte(vm, address) << 8);
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
        case DEV_NONE:
            log_warn("Device accessed of type DEV_NONE, returning x00");
            return 0x00;            
        default:
            log_error("Device accessed of unknown type (%d)", dev->type);
            exit(1);
            break;
    }
}

void vm_write_byte(ADDR_SPACE *vm, Word_t address, Byte_t value) {
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
            log_error("Tried to write to ROM at address %d", address);
            break;
        case DEV_RAM:
            ram_write_byte(dev->device.ram, address - dev->address_begin, value);
            break;
        default: 
            log_error("Device accessed of unknown type (%d)", dev->type);
            break;
    }    
}
void vm_write_word(ADDR_SPACE *vm, Word_t address, Word_t value) {
    vm_write_byte(vm, address, (Byte_t) value >> 8);
    vm_write_byte(vm, address + 1, (Byte_t) value);
}

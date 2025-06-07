#include "cpu.h"
#include "mem.h"

#include <stdlib.h>

CPU *cpu_init(ADDR_SPACE *address_space) {
    CPU *cpu = malloc(sizeof(CPU));
    cpu->address_space = address_space;
    cpu->PC = vm_read_word(address_space, 0xFFFC);

    /* TODO do more things */

    return cpu;
}
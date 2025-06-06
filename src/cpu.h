#ifndef CPU_H
#define CPU_H


#include "mem.h"
#include "types.h"

#include <stdint.h>


typedef struct {
    Word_t PC;
    Word_t SP;
    Byte_t Accumulator;
    Byte_t IndexRegX;
    Byte_t IndexRegY;
    Byte_t STAT;

    ADDR_SPACE *address_space;
} CPU;

CPU *cpu_init(ADDR_SPACE *address_space) {
    CPU *cpu = malloc(sizeof(CPU));
    cpu->address_space = address_space;
    cpu->PC = vm_read_word(0xFFFC);
}

#endif
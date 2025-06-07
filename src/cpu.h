#ifndef CPU_H
#define CPU_H


#include "mem.h"
#include "types.h"

#include <stdint.h>

#define CARRY_BIT 0b00000001
#define ZERO_BIT 0b00000010
#define INTHUP_DISABLE_BIT 0b00000100
#define DEC_MOD_BIT 0b00001000
#define BRK_BIT 0b00010000
#define OVERFLOW_BIT 0b00100000
#define NEGATIVE_BIT 0b01000000


typedef struct {
    Word_t PC;
    Word_t SP;
    Byte_t Accumulator;
    Byte_t IndexRegX;
    Byte_t IndexRegY;
    Byte_t STAT;

    ADDR_SPACE *address_space;
} CPU;

CPU *cpu_init(ADDR_SPACE *address_space);

#endif
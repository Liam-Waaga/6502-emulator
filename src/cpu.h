#ifndef CPU_H
#define CPU_H


#include "mem.h"
#include "types.h"

#include <stdint.h>


struct CPU {
    Word_t PC;
    Word_t SP;
    Byte_t Accumulator;
    Byte_t IndexRegX;
    Byte_t IndexRegY;
    Byte_t STAT;

    struct ADDR_SPACE *address_space;
};

#endif
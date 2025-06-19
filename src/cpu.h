/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


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
#define ALWAYS_SET_BIT 0b00100000
#define OVERFLOW_BIT 0b01000000
#define NEGATIVE_BIT 0b10000000

#define CPU_STAT_DEFAULT ALWAYS_SET_BIT


typedef struct {
    Word_t PC;
    Word_t SP;
    Byte_t Accumulator;
    Byte_t IndexRegX;
    Byte_t IndexRegY;
    Byte_t STAT;

    ADDR_SPACE *address_space;
} CPU;


/* Assumes resposibility of the ADDR_SPACE struct and all its resources */
CPU *cpu_init(ADDR_SPACE *address_space);

void cpu_deinit(CPU *cpu);

#endif

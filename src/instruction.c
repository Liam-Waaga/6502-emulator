#include "instruction.h"
#include "cpu.h"
#include "log/log.h"
#include "mem.h"
#include "clock.h"

#include <stdlib.h>

void execute_instruction(CPU *cpu, unsigned char opcode) {
    log_info("Running opcode 0x%x", opcode);
    switch (opcode) {
        case 0x69:
            ADC_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x65:
            ADC_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;
            
        case 0x75:
            ADC_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(4, 0);
            break;
            
        case 0x6D:
            ADC_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
            
        case 0x7D:
            ADC_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
            
        case 0x79:
            ADC_AY(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
            
        case 0x61:
            ADC_INX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;

        case 0x71:
            ADC_INY(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;
        
        default:
            log_error("Opcode '%x' not found", opcode);
            exit(1);
    }
}



/* ADC */

void do_ADC(CPU *cpu, int operand, int result) {
    if (result > 0xff) {
        cpu->STAT = cpu->STAT | CARRY_BIT;
    }

    result = result & 0xff;

    if ((~(cpu->Accumulator ^ operand) & (cpu->Accumulator ^ result)) & 0x80) {
        cpu->STAT = cpu->STAT | OVERFLOW_BIT;
    }

    cpu->Accumulator = (Byte_t) result;
}

void ADC_IM(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, cpu->PC + 1);
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;
    
    do_ADC(cpu, operand, result);
}

void ADC_ZP(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1));
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;
    
    do_ADC(cpu, operand, result);
}

void ADC_ZPX(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)) + cpu->IndexRegX;
    operand %= 256;
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;
    
    do_ADC(cpu, operand, result);
}

void ADC_A(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1));
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;
    
    do_ADC(cpu, operand, result);
}

void ADC_AX(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX);
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;

    do_ADC(cpu, operand, result);
}

void ADC_AY(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegY);
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;

    do_ADC(cpu, operand, result);
}

void ADC_INX(CPU *cpu) {
                  /* read the final address */
    int operand = vm_read_byte(cpu->address_space, 
                  /* read the address containing the final address */
                  vm_read_word(cpu->address_space, (vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX) % 256));

    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;

    do_ADC(cpu, operand, result);
}

void ADC_INY(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)) + cpu->IndexRegY);
    int result = cpu->Accumulator + (cpu->STAT & CARRY_BIT) + operand;

    do_ADC(cpu, operand, result);
}



/* AND */

void do_AND(CPU *cpu, int o1){
    int o2 = cpu->Accumulator;
    int result = o1 & o2;
    if (cpu->Accumulator == 0)
        cpu->STAT = cpu->STAT | ZERO_BIT;
    if ((o1 & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
    cpu->Accumulator = result;
}

void AND_IM(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, cpu->PC + 1);
    do_AND(cpu, operand1);
};
void AND_ZP(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1));
    do_AND(cpu, operand1);
};
void AND_ZPX(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX);
    do_AND(cpu, operand1);
};
void AND_A(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1));
    do_AND(cpu, operand1);
}
void AND_AX(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX);
    do_AND(cpu, operand1);
};
void AND_AY(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegY);
    do_AND(cpu, operand1);
};
void AND_INX(CPU *cpu) {
    int operand1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, (vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX) % 256));;
    do_AND(cpu, operand1);
};
void AND_INY(CPU *cpu) {
    int operand = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)) + cpu->IndexRegY);
    do_AND(cpu, operand);
};


/* ASL */

void ASL_AC(CPU *cpu) {
    if (cpu->Accumulator == 0)
        cpu->STAT |= ZERO_BIT;
    if ((cpu->Accumulator & 0b10000000) > 0)
        cpu->STAT |= CARRY_BIT;
    else
        cpu->STAT &= ~CARRY_BIT;

    cpu->Accumulator <<= 1;
    if ((cpu->STAT & CARRY_BIT) > 0)
        cpu->Accumulator++;

    if ((cpu->Accumulator & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
};

void ASL_ZP(CPU *cpu) {
    Word_t address = vm_read_byte(cpu->address_space, cpu->PC + 1);
    address %= 256;
    const Byte_t value = vm_read_byte(cpu->address_space, address);

    if (value == 0)
        cpu->STAT |= ZERO_BIT;
    if ((value & 0b10000000) > 0)
        cpu->STAT |= CARRY_BIT;
    else
        cpu->STAT &= ~CARRY_BIT;

    vm_write_byte(cpu->address_space, address, (value << 1) + (((cpu->STAT & CARRY_BIT) > 0) ? 1 : 0));

    if ((value & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
};

void ASL_ZPX(CPU *cpu) {
    Word_t address = vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX;
    address %= 256;
    const Byte_t value = vm_read_byte(cpu->address_space, address);

    if (value == 0)
        cpu->STAT |= ZERO_BIT;
    if ((value & 0b10000000) > 0)
        cpu->STAT |= CARRY_BIT;
    else
        cpu->STAT &= ~CARRY_BIT;

    vm_write_byte(cpu->address_space, address, (value << 1) + (((cpu->STAT & CARRY_BIT) > 0) ? 1 : 0));

    if ((value & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
};

void ASL_A(CPU *cpu) {
    Word_t address = vm_read_word(cpu->address_space, cpu->PC + 1);
    const Byte_t value = vm_read_byte(cpu->address_space, address);

    if (value == 0)
        cpu->STAT |= ZERO_BIT;
    if ((value & 0b10000000) > 0)
        cpu->STAT |= CARRY_BIT;
    else
        cpu->STAT &= ~CARRY_BIT;

    vm_write_byte(cpu->address_space, address, (value << 1) + (((cpu->STAT & CARRY_BIT) > 0) ? 1 : 0));

    if ((value & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
}

void ASL_AX(CPU *cpu) {
    Word_t address = vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX;
    const Byte_t value = vm_read_byte(cpu->address_space, address);

    if (value == 0)
        cpu->STAT |= ZERO_BIT;
    if ((value & 0b10000000) > 0)
        cpu->STAT |= CARRY_BIT;
    else
        cpu->STAT &= ~CARRY_BIT;

    vm_write_byte(cpu->address_space, address, (value << 1) + (((cpu->STAT & CARRY_BIT) > 0) ? 1 : 0));

    if ((value & 0b10000000) > 0)
        cpu->STAT |= NEGATIVE_BIT;
};


/* BCC */

void BCC_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if (!((cpu->STAT & CARRY_BIT) > 0))
    cpu->PC += offset;
}


/* BCS */

void BCS_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if ((cpu->STAT & CARRY_BIT) > 0)
        cpu->PC += offset;
}


/* BEQ */

void BEQ_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if ((cpu->STAT & ZERO_BIT) > 0)
        cpu->PC += offset;
}


/* BIT */

void BIT_ZP(CPU *cpu) {
    int acc = cpu->Accumulator;
    do_AND(cpu, vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)));
    if (vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)) & 0b01000000)
        cpu->STAT |= OVERFLOW_BIT;
    cpu->Accumulator = acc;
};
void BIT_A(CPU *cpu) {
    int acc = cpu->Accumulator;
    do_AND(cpu, vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1)));
    if (vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1)) & 0b01000000)
        cpu->STAT |= OVERFLOW_BIT;
    cpu->Accumulator = acc;
}


/* BMI */

void BMI_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if ((cpu->STAT & NEGATIVE_BIT) > 0)
        cpu->PC += offset;
}


/* BNE */

void BNE_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if (!((cpu->STAT & ZERO_BIT) > 0))
        cpu->PC += offset;
}


/* BPL */

void BPL_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* BRK */

void BRK_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* BVC */

void BVC_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* BVS */

void BVS_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CLC */

void CLC_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CLD */

void CLD_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CLI */

void CLI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CLV */

void CLV_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CMP */

void CMP_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void CMP_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CMP_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* CPX */

void CPX_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CPX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CPX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* CPY */

void CPY_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CPY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void CPY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* DEC */

void DEC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void DEC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void DEC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void DEC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* DEX */

void DEX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* DEY*/

void DEY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* EOR */

void EOR_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void EOR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void EOR_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* INC */

void INC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void INC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void INC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void INC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* INX */

void INX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* INY */

void INY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* JMP */

void JMP_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void JMP_IN(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* JSR */

void JSR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* LDA */

void LDA_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDA_ZPX(CPU *cp) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void LDA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDA_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDA_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* LDX */

void LDX_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDX_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void LDX_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* LDY */

void LDY_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDY_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LDY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void LDY_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* LSR */

void LSR_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LSR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LSR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void LSR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void LSR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* NOP */

void NOP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* ORA */

void ORA_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ORA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ORA_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ORA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void ORA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ORA_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ORA_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* PHA */

void PHA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* PHP */

void PHP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* PLA */

void PLA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* PLP */

void PLP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* ROL */

void ROL_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROL_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROL_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROL_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void ROL_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* ROR */

void ROR_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void ROR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void ROR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* RTI */

void RTI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* RTS */

void RTS_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* SBC */

void SBC_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void SBC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void SBC_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* SED */

void SED_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* SEI */

void SEI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* STA */

void STA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STA_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
void STA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STA_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STA_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STA_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};


/* STX */

void STX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STX_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* STY */

void STY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STY_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
};
void STY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TAX */

void TAX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TAY */

void TAY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TSX */

void TSX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TXA */

void TXA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TXS */

void TXS_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* TYA */

void TYA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}
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

        case 0x29:
            AND_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x25:
            AND_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0x35:
            AND_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(4, 0);
            break;

        case 0x2D:
            AND_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0x3D:
            AND_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0x39:
            AND_AY(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0x21:
            AND_INX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;

        case 0x31:
            AND_INY(cpu);
            cpu->PC += 2;
            schedule_clock_wait(5, 0);
            break;

        case 0x0A:
            ASL_AC(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;

        case 0x06:
            ASL_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(5, 0);
            break;

        case 0x16:
            ASL_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0x0E:
            ASL_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(6, 0);
            break;

        case 0x1E:
            ASL_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(7, 0);
            break;

        case 0x90:
            BCC_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xB0:
            BCS_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xF0:
            BEQ_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x24:
            BIT_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0x2C:
            BIT_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0x30:
            BMI_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xD0:
            BNE_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x10:
            BPL_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x50:
            BVC_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x70:
            BVS_R(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0x18:
            CLC_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;

        case 0xD8:
            CLD_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;

        case 0x58:
            CLI_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;

        case 0xB8:
            CLV_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;

        case 0xC9:
            CMP_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xC5:
            CMP_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0xD5:
            CMP_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(4, 0);
            break;

        case 0xCD:
            CMP_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0xDD:
            CMP_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0xD9:
            CMP_AY(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0xC1:
            CMP_INX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;

        case 0xD1:
            CMP_INY(cpu);
            cpu->PC += 2;
            schedule_clock_wait(5, 0);
            break;

        case 0xE0:
            CPX_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xE4:
            CPX_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0xEC:
            CPX_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0xC0:
            CPY_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;

        case 0xC4:
            CPY_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;

        case 0xCC:
            CPY_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;

        case 0xC6:
            DEC_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(5, 0);
            break;

        case 0xD6:
            DEC_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;

        case 0xCE:
            DEC_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(6, 0);
            break;
        
        case 0xDE:
            DEC_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(7, 0);
            break;
        
        case 0xCA:
            DEX_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;
        
        case 0x88:
            DEY_I(cpu);
            cpu->PC += 1;
            schedule_clock_wait(2, 0);
            break;
        
        case 0x49:
            EOR_IM(cpu);
            cpu->PC += 2;
            schedule_clock_wait(2, 0);
            break;
        
        case 0x45:
            EOR_ZP(cpu);
            cpu->PC += 2;
            schedule_clock_wait(3, 0);
            break;
        
        case 0x55:
            EOR_ZPX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(4, 0);
            break;
        
        case 0x4D:
            EOR_A(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
        
        case 0x5D:
            EOR_AX(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
        
        case 0x59:
            EOR_AY(cpu);
            cpu->PC += 3;
            schedule_clock_wait(4, 0);
            break;
        
        case 0x41:
            EOR_INX(cpu);
            cpu->PC += 2;
            schedule_clock_wait(6, 0);
            break;
        
        case 0x51:
            EOR_INY(cpu);
            cpu->PC += 2;
            schedule_clock_wait(5, 0);
            break;
        
        /* TODO, add the rest of the official instruction opcodes */

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
    int operand1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, (vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX) % 256));
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
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if (!((cpu->STAT & NEGATIVE_BIT) > 0))
        cpu->PC += offset;
}


/* BRK */

void BRK_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
    exit(1);
}


/* BVC */

void BVC_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if (!((cpu->STAT & OVERFLOW_BIT) > 0))
        cpu->PC += offset;
}


/* BVS */

void BVS_R(CPU *cpu) {
    Byte_signed_t offset = vm_read_byte(cpu->address_space, cpu->PC + 1);
    if ((cpu->STAT & OVERFLOW_BIT) > 0)
        cpu->PC += offset;
}


/* CLC */

void CLC_I(CPU *cpu) {
    cpu->STAT &= ~CARRY_BIT;
}


/* CLD */

void CLD_I(CPU *cpu) {
    cpu->STAT &= ~DEC_MOD_BIT;
}


/* CLI */

void CLI_I(CPU *cpu) {
    cpu->STAT &= ~INTHUP_DISABLE_BIT;
}


/* CLV */

void CLV_I(CPU *cpu) {
    cpu->STAT &= ~OVERFLOW_BIT;
}


/* CMP */

void do_CMP(CPU *cpu, int op1) {
    if (cpu->Accumulator == op1)
        cpu->STAT |= ZERO_BIT;
    if (cpu->Accumulator >= op1)
        cpu->STAT |= CARRY_BIT;
    if ((cpu->Accumulator - op1) & 0b10000000)
        cpu->STAT |= NEGATIVE_BIT;
}

void CMP_IM(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, cpu->PC + 1);
    do_CMP(cpu, op1);
};
void CMP_ZP(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1));
    do_CMP(cpu, op1);
};
void CMP_ZPX(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, (vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX) % 256);
    do_CMP(cpu, op1);
};
void CMP_A(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1));
    do_CMP(cpu, op1);
}
void CMP_AX(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX);
    do_CMP(cpu, op1);
};
void CMP_AY(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1) + cpu->IndexRegY);
    do_CMP(cpu, op1);
};
void CMP_INX(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, (vm_read_byte(cpu->address_space, cpu->PC + 1) + cpu->IndexRegX) % 256));
    do_CMP(cpu, op1);
};
void CMP_INY(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1)) + cpu->IndexRegY);
    do_CMP(cpu, op1);
};


/* CPX */

void do_CPX(CPU *cpu, int op1) {
    if (cpu->IndexRegX == op1)
        cpu->STAT |= ZERO_BIT;
    if (cpu->IndexRegX >= op1)
        cpu->STAT |= CARRY_BIT;
    if ((cpu->IndexRegX - op1) & 0b10000000)
        cpu->STAT |= NEGATIVE_BIT;
}

void CPX_IM(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, cpu->PC + 1);
    do_CPX(cpu, op1);
};
void CPX_ZP(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1));
    do_CPX(cpu, op1);
};
void CPX_A(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1));
    do_CPX(cpu, op1);
}


/* CPY */

void do_CPY(CPU *cpu, int op1) {
    if (cpu->IndexRegY == op1)
        cpu->STAT |= ZERO_BIT;
    if (cpu->IndexRegY >= op1)
        cpu->STAT |= CARRY_BIT;
    if ((cpu->IndexRegY - op1) & 0b10000000)
        cpu->STAT |= NEGATIVE_BIT;
}

void CPY_IM(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, cpu->PC + 1);
    do_CPX(cpu, op1);
};
void CPY_ZP(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_byte(cpu->address_space, cpu->PC + 1));
    do_CPX(cpu, op1);
};
void CPY_A(CPU *cpu) {
    int op1 = vm_read_byte(cpu->address_space, vm_read_word(cpu->address_space, cpu->PC + 1));
    do_CPX(cpu, op1);
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
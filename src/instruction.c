#include "instruction.h"
#include "log/log.h"

#include <stdlib.h>

void execute_instruction(CPU *cpu, unsigned char opcode) {
    switch (opcode) {
        default:
            log_error("Opcode '%x' not found", opcode);
            exit(1);
    }
}



/* ADC */

void ADC_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void ADC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADC_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* AND */

void AND_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void AND_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void AND_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* ASL */

void ADL_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADL_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADL_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ADL_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void ADL_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* BCC */

void BCC_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BCS */

void BCS_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BEQ */

void BEQ_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BIT */

void BIT_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void BIT_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BMI */

void BMI_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BNE */

void BNE_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BPL */

void BPL_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BRK */

void BRK_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BVC */

void BVC_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* BVS */

void BVS_R(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CLC */

void CLC_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CLD */

void CLD_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CLI */

void CLI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CLV */

void CLV_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CMP */

void CMP_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void CMP_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CMP_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* CPX */

void CPX_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CPX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CPX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* CPY */

void CPY_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CPY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void CPY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* DEC */

void DEC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void DEC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void DEC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void DEC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* DEX */

void DEX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* DEY*/

void DEY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* EOR */

void EOR_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void EOR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void EOR_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* INC */

void INC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void INC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void INC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void INC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* INX */

void INX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* INY */

void INY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* JMP */

void JMP_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void JMP_IN(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* JSR */

void JSR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* LDA */

void LDA_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDA_ZPX(CPU *cp) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void LDA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDA_INX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDA_INY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* LDX */

void LDX_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDX_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void LDX_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* LDY */

void LDY_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDY_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LDY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void LDY_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* LSR */

void LSR_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LSR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LSR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void LSR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void LSR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* NOP */

void NOP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* ORA */

void ORA_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ORA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ORA_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ORA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void ORA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ORA_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ORA_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* PHA */

void PHA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* PHP */

void PHP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* PLA */

void PLA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* PLP */

void PLP_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* ROL */

void ROL_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROL_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROL_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROL_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void ROL_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* ROR */

void ROR_AC(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROR_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROR_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void ROR_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void ROR_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* RTI */

void RTI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* RTS */

void RTS_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* SBC */

void SBC_IM(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void SBC_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void SBC_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* SED */

void SED_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* SEI */

void SEI_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* STA */

void STA_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STA_ZPX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STA_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
void STA_AX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STA_AY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STA_IX(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STA_IY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};


/* STX */

void STX_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STX_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STX_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* STY */

void STY_ZP(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STY_ZPY(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
};
void STY_A(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TAX */

void TAX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TAY */

void TAY_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TSX */

void TSX_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TXA */

void TXA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TXS */

void TXS_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}


/* TYA */

void TYA_I(CPU *cpu) {
    log_error("Unimplemented, %s:%d", __FILE__, __LINE__);
}
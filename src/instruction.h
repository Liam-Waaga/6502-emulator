/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include "cpu.h"

void execute_instruction(CPU *cpu, unsigned char opcode);

/* Instruction Functions */
/* http://www.6502.org/users/obelisk/6502/reference.html */

/* ADC */

void ADC_IM(CPU *cpu);
void ADC_ZP(CPU *cpu);
void ADC_ZPX(CPU *cpu);
void ADC_A(CPU *cpu);
void ADC_AX(CPU *cpu);
void ADC_AY(CPU *cpu);
void ADC_INX(CPU *cpu);
void ADC_INY(CPU *cpu);


/* AND */

void AND_IM(CPU *cpu);
void AND_ZP(CPU *cpu);
void AND_ZPX(CPU *cpu);
void AND_ZPY(CPU *cpu);
void AND_A(CPU *cpu);
void AND_AX(CPU *cpu);
void AND_AY(CPU *cpu);
void AND_INX(CPU *cpu);
void AND_INY(CPU *cpu);


/* ASL */

void ASL_AC(CPU *cpu);
void ASL_ZP(CPU *cpu);
void ASL_ZPX(CPU *cpu);
void ASL_A(CPU *cpu);
void ASL_AX(CPU *cpu);


/* BCC */

void BCC_R(CPU *cpu);


/* BCS */

void BCS_R(CPU *cpu);


/* BEQ */

void BEQ_R(CPU *cpu);


/* BIT */

void BIT_ZP(CPU *cpu);
void BIT_A(CPU *cpu);


/* BMI */

void BMI_R(CPU *cpu);


/* BNE */

void BNE_R(CPU *cpu);


/* BPL */

void BPL_R(CPU *cpu);


/* BRK */

void BRK_R(CPU *cpu);


/* BVC */

void BVC_R(CPU *cpu);


/* BVS */

void BVS_R(CPU *cpu);


/* CLC */

void CLC_I(CPU *cpu);


/* CLD */

void CLD_I(CPU *cpu);


/* CLI */

void CLI_I(CPU *cpu);


/* CLV */

void CLV_I(CPU *cpu);


/* CMP */

void CMP_IM(CPU *cpu);
void CMP_ZP(CPU *cpu);
void CMP_ZPX(CPU *cpu);
void CMP_A(CPU *cpu);
void CMP_AX(CPU *cpu);
void CMP_AY(CPU *cpu);
void CMP_INX(CPU *cpu);
void CMP_INY(CPU *cpu);


/* CPX */

void CPX_IM(CPU *cpu);
void CPX_ZP(CPU *cpu);
void CPX_A(CPU *cpu);


/* CPY */

void CPY_IM(CPU *cpu);
void CPY_ZP(CPU *cpu);
void CPY_A(CPU *cpu);


/* DEC */

void DEC_ZP(CPU *cpu);
void DEC_ZPX(CPU *cpu);
void DEC_A(CPU *cpu);
void DEC_AX(CPU *cpu);


/* DEX */

void DEX_I(CPU *cpu);


/* DEY*/

void DEY_I(CPU *cpu);


/* EOR */

void EOR_IM(CPU *cpu);
void EOR_ZP(CPU *cpu);
void EOR_ZPX(CPU *cpu);
void EOR_A(CPU *cpu);
void EOR_AX(CPU *cpu);
void EOR_AY(CPU *cpu);
void EOR_INX(CPU *cpu);
void EOR_INY(CPU *cpu);


/* INC */

void INC_ZP(CPU *cpu);
void INC_ZPX(CPU *cpu);
void INC_A(CPU *cpu);
void INC_AX(CPU *cpu);


/* INX */

void INX_I(CPU *cpu);


/* INY */

void INY_I(CPU *cpu);


/* JMP */

void JMP_A(CPU *cpu);
void JMP_IN(CPU *cpu);


/* JSR */

void JSR_A(CPU *cpu);


/* LDA */

void LDA_IM(CPU *cpu);
void LDA_ZP(CPU *cpu);
void LDA_ZPX(CPU *cpu);
void LDA_A(CPU *cpu);
void LDA_AX(CPU *cpu);
void LDA_INX(CPU *cpu);
void LDA_INY(CPU *cpu);


/* LDX */

void LDX_IM(CPU *cpu);
void LDX_ZP(CPU *cpu);
void LDX_ZPY(CPU *cpu);
void LDX_A(CPU *cpu);
void LDX_AY(CPU *cpu);


/* LDY */

void LDY_IM(CPU *cpu);
void LDY_ZP(CPU *cpu);
void LDY_ZPY(CPU *cpu);
void LDY_A(CPU *cpu);
void LDY_AY(CPU *cpu);


/* LSR */

void LSR_AX(CPU *cpu);
void LSR_ZP(CPU *cpu);
void LSR_ZPX(CPU *cpu);
void LSR_A(CPU *cpu);
void LSR_AX(CPU *cpu);


/* NOP */

void NOP_I(CPU *cpu);


/* ORA */

void ORA_IM(CPU *cpu);
void ORA_ZP(CPU *cpu);
void ORA_ZPX(CPU *cpu);
void ORA_A(CPU *cpu);
void ORA_AX(CPU *cpu);
void ORA_IX(CPU *cpu);
void ORA_IY(CPU *cpu);


/* PHA */

void PHA_I(CPU *cpu);


/* PHP */

void PHP_I(CPU *cpu);


/* PLA */

void PLA_I(CPU *cpu);


/* PLP */

void PLP_I(CPU *cpu);


/* ROL */

void ROL_AC(CPU *cpu);
void ROL_ZP(CPU *cpu);
void ROL_ZPX(CPU *cpu);
void ROL_A(CPU *cpu);
void ROL_AX(CPU *cpu);


/* ROR */

void ROR_AC(CPU *cpu);
void ROR_ZP(CPU *cpu);
void ROR_ZPX(CPU *cpu);
void ROR_A(CPU *cpu);
void ROR_AX(CPU *cpu);


/* RTI */

void RTI_I(CPU *cpu);


/* RTS */

void RTS_I(CPU *cpu);


/* SBC */

void SBC_IM(CPU *cpu);
void SBC_ZP(CPU *cpu);
void SBC_ZPX(CPU *cpu);
void SBC_A(CPU *cpu);
void SBC_AX(CPU *cpu);
void SBC_AY(CPU *cpu);
void SBC_IX(CPU *cpu);
void SBC_IY(CPU *cpu);


/* SED */

void SED_I(CPU *cpu);


/* SEI */

void SEI_I(CPU *cpu);


/* STA */

void STA_ZP(CPU *cpu);
void STA_ZPX(CPU *cpu);
void STA_A(CPU *cpu);
void STA_AX(CPU *cpu);
void STA_AY(CPU *cpu);
void STA_IX(CPU *cpu);
void STA_IY(CPU *cpu);


/* STX */

void STX_ZP(CPU *cpu);
void STX_ZPY(CPU *cpu);
void STX_A(CPU *cpu);


/* STY */

void STY_ZP(CPU *cpu);
void STY_ZPY(CPU *cpu);
void STY_A(CPU *cpu);


/* TAX */

void TAX_I(CPU *cpu);


/* TAY */

void TAY_I(CPU *cpu);


/* TSX */

void TAY_I(CPU *cpu);


/* TXA */

void TXA_I(CPU *cpu);


/* TXS */

void TXS_I(CPU *cpu);


/* TYA */

void TYA_I(CPU *cpu);


#endif

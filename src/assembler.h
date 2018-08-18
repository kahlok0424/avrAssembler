#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include "Tokenizer.h"

#define TWO_BYTE  2
#define FOUR_BYTE 4
//#define TokenMatches(token,str2cmp)  (strcmp(token,str2cmp )== 0)

typedef int(*InstructionFuncPtr)(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);

typedef struct{
  char *name;
  InstructionFuncPtr assemble;
}InstructionMap;

//instructions of no operand
int sec(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sen(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cln(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sez(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clz(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sei(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cli(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int ses(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cls(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sev(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clv(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int set(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clt(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int seh(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clh(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int nop(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sleep(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int ijmp(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int eijmp(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int icall(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int eicall(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int ret(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int reti(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int wdr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int breakAVR(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);

//instruction with one operand
int inc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int dec(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int com(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int neg(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int push(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int pop(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int lsr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int asr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int swap(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int lsl(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int clr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int tst(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int ser(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int rol(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);

//instrutions with two operands (Rd , Rr)
int addRdRr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int adc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sub(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int sbc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int andRdRr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int orRdRr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int eor(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int mul(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cpse(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cp(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int cpc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int mov(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int muls(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
int mulsu(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int fmul(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int fmuls(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int fmulsu(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);

//branch instructions
int breq(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brne(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brcs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brcc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brsh(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brlo(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brmi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brpl(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brge(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brlt(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brhs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brhc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brts(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brtc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brvs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brvc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brie(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int brid(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int rjmp(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int rcall(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);

//instructions with Rd,K8 operands
int andi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int ori(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int subi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int sbci(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int ldi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int cbr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int sbr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int cpi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
int adiw(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);

char *convertToLowerCase(char *str);
int assembleOneInstruction(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);
void encodingNoOperand(uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);
void encodingRdRr(int Rd ,int Rr, uint8_t opcode, uint8_t codeMemoryPtr[]);
void encodingBranch(uint8_t k, uint16_t opcode, uint8_t codeMemoryPtr[]);
void encodingRdK8(uint8_t Rd , uint16_t K, uint16_t opCode, uint8_t codeMemoryPtr[]);

#endif // _ASSEMBLER_H

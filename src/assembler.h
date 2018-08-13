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

char *convertToLowerCase(char *str);
int assembleOneInstruction(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);
void encodingNoOperand(uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);

#endif // _ASSEMBLER_H

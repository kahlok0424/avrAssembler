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

char *convertToLowerCase(char *str);
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

int assembleOneInstruction(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);

static const InstructionMap instructionsMapTable[] = {
  {"inc" , inc},
  {"dec" , dec},
  {"com" , com}
};

#endif // _ASSEMBLER_H

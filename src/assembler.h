#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include "Tokenizer.h"

#define TWO_BYTE  2
#define TokenMatches(token,str2cmp)  (strcmp(token,str2cmp )== 0)

typedef struct InstructionMap InstructionMap;
typedef int(*InstructionFuncPtr)(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);

struct InstructionMap{
  char *name;
  InstructionFuncPtr assemble;
};

/*InstructionMap instructionMapTable[] = {
  {"INC" , inc},
  {"DEC" , dec}
};*/

char *convertToLowerCase(char *str);
void sec(uint8_t codeMemoryPtr[]);
void inc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void dec(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void com(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void neg(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void push(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void pop(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void lsr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void asr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void swap(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void lsl(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void clr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void tst(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void rol(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);
void ser(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]);

//uint8_t *encodingRd(int Rd ,uint8_t opcode1, uint8_t opcode2);
void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]);

#endif // _ASSEMBLER_H

#ifndef _GETOPERAND_H
#define _GETOPERAND_H
#include "Tokenizer.h"

#define   R0    0
#define   R16   16
#define   R31   31

int getRegister(Tokenizer *tokenizer, int minReg , int maxReg);
void getNextTokenAndVerify(Tokenizer *tokenizer , char *str);
void getRd(Tokenizer *tokenizer , uint16_t *values , int minReg ,int maxReg);    //example inc Rd
void getRdRr(Tokenizer *tokenizer , uint16_t *value ,  int minReg , int maxReg);   //example add Rd ,rr

#endif // _GETOPERAND_H

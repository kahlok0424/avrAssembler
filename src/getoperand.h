#ifndef _GETOPERAND_H
#define _GETOPERAND_H
#include "Tokenizer.h"

#define   R0    0
#define   R16   16
#define   R31   31
#define   R23   23

#define   Xaddress      201
#define   XPlus         202
#define   XMinus        203
#define   Yaddress      204
#define   YPlus         205
#define   YMinus        206
#define   Zaddress      207
#define   ZPlus         208
#define   ZMinus        209
#define   XYZ           210

int getRegister(Tokenizer *tokenizer, int minReg , int maxReg);
void getNextTokenAndVerify(Tokenizer *tokenizer , char *str);
void getRd(Tokenizer *tokenizer , uint16_t *values , int minReg ,int maxReg);    //example inc Rd
void getRdRr(Tokenizer *tokenizer , uint16_t *value ,  int minReg , int maxReg);   //example add Rd ,rr
uint16_t getK(Tokenizer *tokenizer,int min , int max );

#endif // _GETOPERAND_H

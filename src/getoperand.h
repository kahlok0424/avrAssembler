#ifndef _GETOPERAND_H
#define _GETOPERAND_H
#include "Tokenizer.h"

void getRd(Tokenizer *tokenizer , uint16_t *values);    //example inc Rd
void getRdRr(Tokenizer *tokenizer , uint16_t *value);   //example add Rd ,rr

#endif // _GETOPERAND_H

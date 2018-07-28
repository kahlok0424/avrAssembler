#ifndef Tokenizer_H
#define Tokenizer_H

#include <stdint.h>
#include "Common.h"
#include "Token.h"

#define TOKENIZER_DOLLAR_SIGN_HEX   (1 << 0)

typedef struct {
  char *str;
  int index;
  uint32_t config;
  uint32_t prevStartColumn;
  uint32_t prevLength;
 // Token *previousToken;
  Token *currentToken;
} Tokenizer;

void reinitTokenizer(Tokenizer *tokenizer, char *str);
Tokenizer *createTokenizer(char *stringToTokenize);
void freeTokenizer(Tokenizer *tokenizer);
void configureTokenizer(Tokenizer *tokenizer, uint32_t configuration);
Token *advanceToken(Tokenizer *tokenizer);
Token *getToken(Tokenizer *tokenizer);
Token *peepToken(Tokenizer *tokenizer);

#endif // Tokenizer_H

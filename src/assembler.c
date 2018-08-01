#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getoperand.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "Token.h"
#include "Error.h"
#include "assembler.h"

int inc(char *line){
  Tokenizer *tokenizer;
  tokenizer = createTokenizer(line);
  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  token = getToken(tokenizer);
  if(token->type == TOKEN_IDENTIFIER_TYPE){
    if(TokenMatches(token->str,"inc")){
      freeToken(token);
      getRd(tokenizer ,values);          //last modified : trying to make sure correct values get returned
    }
  }else{
  }
  getRd(tokenizer ,values);
  printf("test : %d" , values[0]);
  int result = 0;
  result = values[0];
  return result;
}

void test_binary(void){
  int i = 0b00111;
  printf("\nbinary number i = %d", i );
}

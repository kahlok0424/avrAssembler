#include <stdio.h>
#include "getoperand.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "Token.h"
#include "Error.h"

/**
 * @param tokenizer [tokenizered operands]
 * @param values    [to store the value behind r/R]
 * Get the token from tokenizer and verify the idetifier is it r/R
 * if not throw an erro
 * if correct , extract the value behind r/R , 0 <= d <= 31
 **/
void getRd(Tokenizer *tokenizer, uint16_t *value){
  Token *token;
  char *operands;

  token = getToken(tokenizer);    //get the first token from tokenizer
  if(token->type != TOKEN_IDENTIFIER_TYPE){
    throwException(ERR_EXPECTING_IDENTIFIER, token, "The element is not identifier");
  }
  operands = ((IdentifierToken *)token->str);

  printf("Testing : %s",operands);
}

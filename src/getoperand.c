#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
  int v1 = 0;

  token = getToken(tokenizer);    //get the first token from tokenizer
  if(token->type != TOKEN_IDENTIFIER_TYPE){
    throwException(ERR_EXPECTING_IDENTIFIER, token, "The element is not identifier");
  }
  operands = ((IdentifierToken *)token->str);
  if(*(operands) != 'R' && *(operands) != 'r' ){
    throwException(ERR_INVALID_IDENTIFIER, token, "Expect R/r but the identifier is %s" , operands);
  }else{
    ++operands;
    /*if(!(isdigit(operands+1))){
      throwException(ERR_INVALID_IDENTIFIER, token, "Expect integer but the identifier is %s" , operands);
    }else{*/
    v1 = atoi(operands);
    if(v1>32 || v1 < 0){
      throwException(ERR_BEYOND_LIMIT, token, "%s beyond the limit of 0 < d < 31" ,token->str );
    }else
    *value = v1;
  }
  //}
}

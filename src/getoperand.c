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
  operands = (token->str);
  if(*(operands) != 'R' && *(operands) != 'r' ){
    throwException(ERR_INVALID_IDENTIFIER, token, "Expect R/r but the identifier is %s" , operands);
  }else{
    if(!(isdigit(operands[1]))){
      throwException(ERR_INVALID_IDENTIFIER, token, "Expect integer but the identifier is %s" , operands);
    }else{
      operands++;
      v1 = atoi(operands);
      if(v1>32 || v1 < 0){
        throwException(ERR_BEYOND_LIMIT, token, "%s beyond the limit of 0 < d < 31" ,token->str );
      }else { *value = v1; }
  }
  }
  freeToken(token);
}

/**
 * @param tokenizer [tokenizered operands]
 * @param value     [to store the value behind r/R]
 * Verify the validity of Rd and Rr
 * If correct ,extract the value of Rd and Rd
 * else throw an test_getRd_given_r12_expect_extract_correctly
 */
void getRdRr(Tokenizer *tokenizer , uint16_t *value){

  Token *token;
  char *operands;
  int v1 = 0;
  int v2 = 0;

  token = getToken(tokenizer);    //get the first token from tokenizer
  if(token->type != TOKEN_IDENTIFIER_TYPE){
    throwException(ERR_EXPECTING_IDENTIFIER, token, "The element is not identifier");
  }
  operands = (token->str);
  if(*(operands) != 'R' && *(operands) != 'r' ){
    throwException(ERR_INVALID_IDENTIFIER, token, "Expect R/r but the identifier is %s" , operands);
  }else{
    if(!(isdigit(operands[1]))){
      throwException(ERR_INVALID_IDENTIFIER, token, "Expect integer but the identifier is %s" , operands);
    }else{
      operands++;
      v1 = atoi(operands);
      if(v1>32 || v1 < 0){
        throwException(ERR_BEYOND_LIMIT, token, "%s beyond the limit of 0 < d < 31" ,token->str );
      }else { *value = v1; }
  }
  }
  freeToken(token);

  token = getToken(tokenizer);
  if(token->type != TOKEN_OPERATOR_TYPE){
    throwException(ERR_INVALID_IDENTIFIER, token, "%s expected comma " ,token->str );
  }else {
    freeToken(token);
  }

  token = getToken(tokenizer);    //get the first token from tokenizer
  if(token->type != TOKEN_IDENTIFIER_TYPE){
    throwException(ERR_EXPECTING_IDENTIFIER, token, "The element is not identifier");
  }
  operands = (token->str);
  if(*(operands) != 'R' && *(operands) != 'r' ){
    throwException(ERR_INVALID_IDENTIFIER, token, "Expect R/r but the identifier is %s" , operands);
  }else{
    if(!(isdigit(operands[1]))){
      throwException(ERR_INVALID_IDENTIFIER, token, "Expect integer but the identifier is %s" , operands);
    }else{
      operands++;
      v2 = atoi(operands);
      if(v2>32 || v2 < 0){
        throwException(ERR_BEYOND_LIMIT, token, "%s beyond the limit of 0 < d < 31" ,token->str );
      }else { *(value+1) = v2; }
  }
  }
  freeToken(token);

}

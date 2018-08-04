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
* @param minReg    [to specify the min register number]
* @param maxReg   [to specify the max register number]
* verify the idetifier to be R/r and then extract the value of register
* if not throw an error
* if extracted , return the value of register
**/
int getRegister(Tokenizer *tokenizer, int minReg , int maxReg){
  Token *token;
  char *operands;
  int regValue = 0;

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
      regValue = atoi(operands);
      if(regValue > maxReg || regValue < minReg){
        throwException(ERR_BEYOND_LIMIT, token, "%s beyond the limit of %d < d < %d" ,token->str,minReg,maxReg );
      }else { }
  }
  }
  freeToken(token);
  return regValue;
}

void getNextTokenAndVerify(Tokenizer *tokenizer , char *str){
  Token *token;
  token = getToken(tokenizer);
  if(token->type == TOKEN_OPERATOR_TYPE){
    if(*(token->str) == (*str) ){
     freeToken(token);   //free the token when finish used
     token = getToken(tokenizer);
     if(token->type == TOKEN_OPERATOR_TYPE){
       //token = getToken(tokenizer);
       //printf("token str = %s" , token->str);
       throwException(ERR_INVALID_OPERATOR, token, "Expected to be not operator , but is %s  " ,token->str );
     }else { pushBackToken(tokenizer ,token); }
    }
     else{
       throwException(ERR_INVALID_OPERATOR, token, "Expected to be %s , but is %s  " ,str,token->str );
    }
  }else {
    throwException(ERR_EXPECTING_OPERATOR, token, "Expected to be an operator, but is %s " ,token->str );
  }
}

/**
 * @param tokenizer [tokenizered operands]
 * @param values    [to store the value behind r/R]
 * Get the token from tokenizer and verify the idetifier is it r/R
 * if not throw an erro
 * if correct , extract the value behind r/R , 0 <= d <= 31
 **/
 void getRd(Tokenizer *tokenizer, uint16_t *value , int minReg , int maxReg){
   *value = getRegister(tokenizer, minReg,maxReg);
 }

//Old but functional code
/*void getRd(Tokenizer *tokenizer, uint16_t *value){
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
}*/

/**
 * @param tokenizer [tokenizered operands]
 * @param value     [to store the value behind r/R]
 * Verify the validity of Rd and Rr
 * If correct ,extract the value of Rd and Rd
 * else throw an test_getRd_given_r12_expect_extract_correctly
 */
void getRdRr(Tokenizer *tokenizer , uint16_t *value , int minReg , int maxReg){
  Token *token;
  *value = getRegister(tokenizer, minReg, maxReg);
  getNextTokenAndVerify(tokenizer , ",");
  *(value+1) =getRegister(tokenizer ,minReg,maxReg);
}

/*void getRdRr(Tokenizer *tokenizer , uint16_t *value){

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
  freeToken(token);   //free the token when finish used

  token = getToken(tokenizer);    //get the second token from tokenizer
  if(token->type != TOKEN_OPERATOR_TYPE){
    throwException(ERR_EXPECTING_OPERATOR, token, "Expected to be an operator, but is %s " ,token->str );
  }else {
        if(*(token->str) != ',' ){
          throwException(ERR_INVALID_OPERATOR, token, "%s expected to be comma " ,token->str );
        }
        else{  freeToken(token); }  //free the token when finish used
  }

  token = getToken(tokenizer);    //get the third token from tokenizer
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
  freeToken(token);   //free the token when finish used

}*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getoperand.h"
#include "assembler.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "Token.h"
#include "Error.h"

char *convertToLowerCase1(char *str)
{
  int i = 0;
  char *buffer;
  buffer = (char*)malloc(strlen(str)+1);
  strcpy(buffer,str);
  //convert the word to lowercase 1 by 1
  while(buffer[i] != '\0')
  {
   buffer[i] = tolower(buffer[i]);
    ++i;
  }
    return buffer;
}

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
    throwException(ERR_INVALID_IDENTIFIER, token, "Expect R/r but the identifier is '%s' " , operands);
  }else{
    if(!(isdigit(operands[1]))){
      throwException(ERR_INVALID_IDENTIFIER, token, "Expect integer but the identifier is '%s' " , operands);
    }else{
      operands++;
      regValue = atoi(operands);
      if(regValue > maxReg || regValue < minReg){
        throwException(ERR_BEYOND_LIMIT, token, " '%s' beyond the limit of %d < d < %d " ,token->str,minReg,maxReg );
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
       throwException(ERR_INVALID_OPERATOR, token, "Expected to be not operator , but is '%s' " ,token->str );
     }else { pushBackToken(tokenizer ,token); }
    }
     else{
       throwException(ERR_INVALID_OPERATOR, token, "Expected to be '%s' , but is '%s' " ,str,token->str );
    }
  }else {
    throwException(ERR_EXPECTING_OPERATOR, token, "Expected to be an operator, but is '%s' " ,token->str );
  }
}

int VerifyToken(Tokenizer *tokenizer , char *str){
  Token *token;
  token = getToken(tokenizer);
    if(*(token->str) == (*str) ){
     freeToken(token);   //free the token when finish used
     return 1;
    }
     else{
       pushBackToken(tokenizer,token);
       return 0;
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

/*void getK(Tokenizer *tokenizer,uint16_t *values ,int min , int max ){

  Token *token;
  char *temp;
  int negPos = 0;
  token = getToken(tokenizer);
  temp = convertToLowerCase1(token->str);

  if( !strcmp(temp, "pc")){
    freeToken(token);
    token = getToken(tokenizer);
      if( token->str == "-"){
        negPos =1;
      }
      else if( token->str == "+"){
        negPos =0;
      }
      else {
        //throwException(ERR_INVALID_OPERATOR,"Expecting + / - but is %s ",token->str);
      }
      printf("values = %d \n" ,negPos);
      printf("str = %s \n" , token->str);
      freeToken(token);
      token = getToken(tokenizer);
      if(token->type == TOKEN_INTEGER_TYPE){
        *values =((IntegerToken *)token)->value;
      }else{
      throwException(ERR_EXPECTING_INTEGER, token, "The element is not integer");
    }
      if(negPos ==1){
      *values = (*values) * -1; }
      else{
      *values = *values ; }
      freeToken(token);
      if( *values > max || *values < min){
        throwException(ERR_BEYOND_LIMIT, token, " '%d' beyond the limit of %d < d < %d " , (*values) ,min,max );
      }else{ }
        }
        else{
         throwException(ERR_EXPECTING_INTEGER, token, "Expect 'PC' but is %s ",token->str);
        }
}*/

uint16_t getConstant(Tokenizer *tokenizer ){
  Token *token;
  token = getToken(tokenizer);
  token = getToken(tokenizer);
  if(token->str == "-"){

  }
}

void getK(Tokenizer *tokenizer,uint16_t *values){

  Token *token;
  char *temp;
  char PositiveNeg;
  int negPos = 0;
  token = getToken(tokenizer);
  temp = convertToLowerCase1(token->str);

  if( !strcmp(temp, "pc")){
    freeToken(token);
    token = getToken(tokenizer);
    PositiveNeg = *(token ->str);
    freeToken(token);
    token = getToken(tokenizer);
      if( PositiveNeg == '-'){
          *values = (((IntegerToken *)token)->value )* -1;
      }
      else if( PositiveNeg == '+'){
          *values = (((IntegerToken *)token)->value);
      }
      else {
        //throwException(ERR_INVALID_OPERATOR,"Expecting + / - but is %s ",token->str);
      }
      freeToken(token);
      /*if( *values > max || *values < min){
        throwException(ERR_BEYOND_LIMIT, token, " '%d' beyond the limit of %d < d < %d " , (*values) ,min,max );
      }else{ }*/
    }
        else{
         throwException(ERR_EXPECTING_INTEGER, token, "Expect 'PC' but is %s ",token->str);
        }
}

void handleXYZ(Tokenizer *tokenizer){

}

 /**
  * [getRdXYZ description]
  * @param tokenizer [description]
  * @param value     [description]
  * verify the validity of Rd,x,y,z and store
  * the respective result
  */
/*void getRdXYZ(Tokenizer *tokenizer,uint16_t *value ,int minReg,int maxReg){

  *value = getRegister(tokenizer ,minReg , maxReg);
  getNextTokenAndVerify(tokenizer ,",");

}

int handleXYZ(Tokenizer *tokenizer , int xyz ){
  Token *token;
  token = getToken(tokenizer);
  if(token->type == TOKEN_IDENTIFIER_TYPE){
  switch(xyz){
    case Xaddress:
      if(token->str == 'x' || token->str == 'X'){
        freeToken(tokenizer);
        token = getToken(tokenizer);
        if(token->str == '+' ){
          return XPlus;
        }else { return Xaddress; }
      } else{ throwException(ERR_INVALID_REGISTER, token, "Expected to be x register, but is '%s' " ,token->str ); }

  }


}
}
*/

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

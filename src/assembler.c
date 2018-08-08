#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getoperand.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "Token.h"
#include "Error.h"
#include "assembler.h"

/**
* REMEMBER TO USE---> git config --global --replace-all user.name "FName LName" before commit
* all instruction should look like this --->   int add(Tokenizer *tokenizer , uint16_t **codeMemoryPtr);
* chat *ptr = *codeMemoryPtr;
* ptr[] = encoding();
* getRdRr(Tokenizer *tokenizer , uint8_t data[]);
**/

char *convertToLowerCase(char *str)
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

/*uint8_t *encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2){
  uint8_t ptr[1];

  if( (Rd) >= 16 ){
    ptr[0]= opcode1 +1;
    ptr[1]= (Rd<<4) + opcode2;
  }else{
    ptr[0]= opcode1;
    ptr[1]= (Rd<<4) + opcode2;
  }
  return ptr;
}*/

void sec(uint8_t codeMemoryPtr[]){
  //uint8_t ptr[1];

  codeMemoryPtr[0] = 0x91;
  codeMemoryPtr[1] = 0x18;
  //(codeMemoryPtr) = ptr;
  //**(codeMemoryPtr+1) = ptr[1];
}

void inc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;
  uint8_t ptr[1] ;
  //codeMemoryPtr = &ptr;

  getRd(tokenizer, values ,R0,R31);
  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x95;
    codeMemoryPtr[1]= (values[0]<<4) + 0x03;
  }else{
    codeMemoryPtr[0]= 0x94;
    codeMemoryPtr[1]= (values[0]<<4) + 0x03;
  }

  printf("ptr code 0 : %x \n" , codeMemoryPtr);
  //printf("ptr code 1 : %x \n" , codeMemoryPtr[1]);
}

void dec(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x95;
    codeMemoryPtr[1]= (values[0]<<4) + 0x0a;
  }else{
    codeMemoryPtr[0]= 0x94;
    codeMemoryPtr[1]= (values[0]<<4) + 0x0a;
  }
}

void ser(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);

    codeMemoryPtr[0]= 0xef;
    codeMemoryPtr[1]= (values[0]<<4) + 0x0f;
}

void test_binary(void){
  int i = 0b00111;
  //printf("\nbinary number i = %d\n", i );
}

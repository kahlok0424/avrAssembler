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

/*uint8_t *encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2){    //has bug
  static uint8_t ptr[1];

  if( (Rd) >= 16 ){
    ptr[0]= opcode1 +1;
    ptr[1]= (Rd<<4) + opcode2;
  }else{
    ptr[0]= opcode1;
    ptr[1]= (Rd<<4) + opcode2;
  }
  return ptr;
}*/

void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]){
  uint8_t ptr[1];

  if( (Rd) >= 16 ){
    codeMemoryPtr[0]= opcode1 +1;
    codeMemoryPtr[1]= (Rd<<4) + opcode2;
  }else{
    codeMemoryPtr[0]= opcode1;
    codeMemoryPtr[1]= (Rd<<4) + opcode2;
  }
}

void sec(uint8_t codeMemoryPtr[]){
  //uint8_t ptr[1];

  codeMemoryPtr[0] = 0x91;
  codeMemoryPtr[1] = 0x18;
  //(codeMemoryPtr) = ptr;
  //**(codeMemoryPtr+1) = ptr[1];
}

/*void inc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //working function before uisng encodingRd()

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
}*/

void inc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){    //increment

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x03 , codeMemoryPtr);
}

void dec(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //decrement

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x0a , codeMemoryPtr);
}

void com(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //One's complement

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x00 , codeMemoryPtr);
}

void neg(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //Two's complement

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x01 , codeMemoryPtr);
}

void push(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //push register to stack

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x92, 0x0f , codeMemoryPtr);
}

void pop(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //Pop stack

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x90, 0x0f , codeMemoryPtr);
}

void lsr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //logical shift right

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x06 , codeMemoryPtr);
}

void asr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //arithmetic shift right

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x05 , codeMemoryPtr);
}

void swap(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //swap nibbles

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x02 , codeMemoryPtr);
}

void lsl(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //logical shift left

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  //encodingRd(values[0] , 0x0c, 0x00 , codeMemoryPtr);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x0f;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x0c;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
}

void clr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //clear register

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  //encodingRd(values[0] , 0x0c, 0x00 , codeMemoryPtr);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x27;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x24;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
}

void tst(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //test for zero or minus

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  //encodingRd(values[0] , 0x0c, 0x00 , codeMemoryPtr);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x23;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x20;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
}

void rol(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //rotate left through carry

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R0,R31);
  //encodingRd(values[0] , 0x0c, 0x00 , codeMemoryPtr);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x1f;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x1c;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
}

void ser(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //set all register bit

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;

  getRd(tokenizer, values ,R16,R31);
  codeMemoryPtr[0]= 0xef;
  codeMemoryPtr[1]= (values[0] << 4) + 0x0f;
}

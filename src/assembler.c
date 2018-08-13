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

InstructionMap instructionsMapTable[] = {
  {"sec" , sec}, //no operand
  {"clc" , clc},
  {"sen" , sen},
  {"cln" , cln},
  {"sez" , sez},
  {"clz" , clz},
  {"sei" , sei},
  {"cli" , cli},
  {"ses" , ses},
  {"cls" , cls},
  {"set" , set},
  {"clt" , clt},
  {"seh" , seh},
  {"clh" , clh},
  {"nop" , nop},
  {"sleep" , sleep},
  {"wdr" , wdr},
  {"break" , breakAVR},
  {"sev" , sev},
  {"clv" , clv},
  {"inc" , inc},  //single operand
  {"dec" , dec},
  {"com" , com},
  {"neg" , neg},
  {"push" , push},
  {"pop" , pop},
  {"lsr" , lsr},
  {"asr" , asr},
  {"swap" , swap},
  {"lsl" , lsl},
  {"clr" , clr},
  {"tst" , tst},
  {"ser" , ser},
  {"rol" , rol}
};


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

void encodingNoOperand(uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]){

    codeMemoryPtr[0]= opcode1;
    codeMemoryPtr[1]= opcode2;
}

void encodingRd(int Rd , uint8_t opcode1, uint8_t opcode2 , uint8_t codeMemoryPtr[]){

  if( (Rd) >= 16 ){
    codeMemoryPtr[0]= opcode1 +1;
    codeMemoryPtr[1]= (Rd<<4) + opcode2;
  }else{
    codeMemoryPtr[0]= opcode1;
    codeMemoryPtr[1]= (Rd<<4) + opcode2;
  }
}

int assembleOneInstruction(Tokenizer *tokenizer , uint8_t *codeMemoryPtr){

  Token *token;
  int tableNo =0;
  int check = 0;
  int rel = 0;
  token = getToken(tokenizer);
  char *temp = convertToLowerCase(token->str);

  if(token->type != TOKEN_IDENTIFIER_TYPE){
    throwException(ERR_EXPECTING_IDENTIFIER, token, "Expected to be identifier , but is '%s' " ,token->str );
  }else{
  for(int i = 0 ; i < 34; i++){
    if( strcmp(temp, instructionsMapTable[i].name) == 0 ){
      tableNo = i;
      check =1;
      break;
    }else{
      check =0;
    }
  }
}

  if(check != 1){
    throwException(ERR_INSTRUCTION_NOT_FOUND, token, "The instruction '%s' is not found in the table " , token->str);
  }
  else {
    rel = instructionsMapTable[tableNo].assemble(tokenizer , codeMemoryPtr);
  }
  freeToken(tokenizer);
  return rel;
}

int sec(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set carry flag

  encodingNoOperand(0x94,0x08,codeMemoryPtr);
  return TWO_BYTE;
}

int clc(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear carry flag

  encodingNoOperand(0x94,0x88,codeMemoryPtr);
  return TWO_BYTE;
}

int sen(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set negative flag

  encodingNoOperand(0x94,0x28,codeMemoryPtr);
  return TWO_BYTE;
}

int cln(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear negative flag

  encodingNoOperand(0x94,0xa8,codeMemoryPtr);
  return TWO_BYTE;
}

int sez(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set zero flag

  encodingNoOperand(0x94,0x18,codeMemoryPtr);
  return TWO_BYTE;
}

int clz(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear zero flag

  encodingNoOperand(0x94,0x98,codeMemoryPtr);
  return TWO_BYTE;
}

int sei(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){ //set global interupt flag

  encodingNoOperand(0x94,0x78,codeMemoryPtr);
  return TWO_BYTE;
}

int cli(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear global interupt flag

  encodingNoOperand(0x94,0xf8,codeMemoryPtr);
  return TWO_BYTE;
}

int ses(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set signed flag

  encodingNoOperand(0x94,0x48,codeMemoryPtr);
  return TWO_BYTE;
}

int cls(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear signed flag

  encodingNoOperand(0x94,0xc8,codeMemoryPtr);
  return TWO_BYTE;
}

int sev(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //overflow flag

  encodingNoOperand(0x94,0x38,codeMemoryPtr);
  return TWO_BYTE;
}

int clv(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear overflow flag

  encodingNoOperand(0x94,0xb8,codeMemoryPtr);
  return TWO_BYTE;
}

int set(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set T flag

  encodingNoOperand(0x94,0x68,codeMemoryPtr);
  return TWO_BYTE;
}

int clt(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear T flag

  encodingNoOperand(0x94,0xe8,codeMemoryPtr);
  return TWO_BYTE;
}

int seh(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //set half carry flag

  encodingNoOperand(0x94,0x58,codeMemoryPtr);
  return TWO_BYTE;
}

int clh(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //clear half carry flag

  encodingNoOperand(0x94,0xd8,codeMemoryPtr);
  return TWO_BYTE;
}

int nop(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //no operation

  encodingNoOperand(0x00,0x00,codeMemoryPtr);
  return TWO_BYTE;
}

int sleep(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //sleep mode

  encodingNoOperand(0x95,0x88,codeMemoryPtr);
  return TWO_BYTE;
}

int wdr(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //watch dog reset

  encodingNoOperand(0x95,0xa8,codeMemoryPtr);
  return TWO_BYTE;
}

int breakAVR(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //break

  encodingNoOperand(0x95,0x98,codeMemoryPtr);
  return TWO_BYTE;
}

int inc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){    //increment

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x03 , codeMemoryPtr);
  return TWO_BYTE;
}

int dec(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //decrement

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x0a , codeMemoryPtr);
  return TWO_BYTE;
}

int com(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //One's complement

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x00 , codeMemoryPtr);
  return TWO_BYTE;
}

int neg(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //Two's complement

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x01 , codeMemoryPtr);
  return TWO_BYTE;
}

int push(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //push register to stack

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x92, 0x0f , codeMemoryPtr);
  return TWO_BYTE;
}

int pop(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //Pop stack

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x90, 0x0f , codeMemoryPtr);
  return TWO_BYTE;
}

int lsr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //logical shift right

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x06 , codeMemoryPtr);
  return TWO_BYTE;
}

int asr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //arithmetic shift right

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x05 , codeMemoryPtr);
  return TWO_BYTE;
}

int swap(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //swap nibbles

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  encodingRd(values[0] , 0x94, 0x02 , codeMemoryPtr);
  return TWO_BYTE;
}

int lsl(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //logical shift left

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);
  //encodingRd(values[0] , 0x0c, 0x00 , codeMemoryPtr);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x0f;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x0c;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
  return TWO_BYTE;
}

int clr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //clear register

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x27;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x24;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
  return TWO_BYTE;
}

int tst(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //test for zero or minus

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x23;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x20;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
  return TWO_BYTE;
}

int rol(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){     //rotate left through carry

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R0,R31);

  if( (*values) >= 16 ){
    codeMemoryPtr[0]= 0x1f;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0] -16 );
  }else{
    codeMemoryPtr[0]= 0x1c;
    codeMemoryPtr[1]= (values[0]<<4) + (values[0]);
  }
  return TWO_BYTE;
}

int ser(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //set all register bit

  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer, values ,R16,R31);

  codeMemoryPtr[0]= 0xef;
  codeMemoryPtr[1]= ((values[0]) <<4 )+ 0x0f;

  return TWO_BYTE;
}

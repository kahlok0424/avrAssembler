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
  {"ijmp" , ijmp},
  {"eijmp" , eijmp},
  {"icall" , icall},
  {"eicall" , eicall},
  {"ret" , ret},
  {"reti" , reti},
  {"wdr" , wdr},
  {"break" , breakAVR},
  {"sev" , sev},
  {"clv" , clv},   //26
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
  {"rol" , rol},  //40
  {"add" , addRdRr},  // RdRr operand
  {"adc" , adc},
  {"sub" , sub},
  {"sbc" , sbc},
  {"and" , andRdRr},
  {"or" , orRdRr},
  {"eor" , eor},
  {"mul" , mul},
  {"cpse" , cpse},
  {"cp" , cp},
  {"cpc" , cpc},
  {"mov" , mov},
  {"muls" , muls},
  {"mulsu" , mulsu},
  {"fmul" , fmul},
  {"fmuls" , fmuls},
  {"fmulsu" , fmulsu},  //57
  {"breq" , breq},
  {"brne" , brne},
  {"brcs" , brcs},
  {"brcc" , brcc},
  {"brsh" , brsh},
  {"brlo" , brlo},
  {"brmi" , brmi},
  {"brpl" , brpl},
  {"brge" , brge},
  {"brlt" , brlt},
  {"brhs" , brhs},
  {"brhc" , brhc},
  {"brts" , brts},
  {"brtc" , brtc},
  {"brvs" , brvs},
  {"brvc" , brvc},
  {"brie" , brie},
  {"brid" , brid},
  {"rjmp" , rjmp},
  {"rcall" , rcall}, //77
  {"andi" , andi},
  {"ori" , ori},
  {"subi" , subi},
  {"sbci" , sbci},
  {"ldi" , ldi},
  {"cbr" , cbr},
  {"sbr" , sbr},
  {"cpi" , cpi},
  {"adiw" , adiw}, //86
  {"call" , call}, //4 byte instrcutions
  {"jmp" , jmp}, //88
  {"bset" , bset},
  {"bclr" , bclr},
  {"sbi" , sbi},
  {"cbi" , cbi},
  {"bst" , bst},
  {"bld" , bld}, //94
  {"sbrc" , sbrc},
  {"sbrs" , sbrs},
  {"sbic" , sbic},
  {"sbis" , sbis},
  {"brbc" , brbc},
  {"brbs" , brbs}, //100
  {"sbiw" , sbiw},
  {"in" , in},
  {"out" , out}, //103
};


/**
* NOTES
* ------------------------------------------------------------------------------------------------
* REMEMBER TO USE---> git config --global --replace-all user.name "FName LName" before commit
* all instruction should look like this --->   int add(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]);
* instructions done : 51
* movw - haven add
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

    codeMemoryPtr[1]= opcode1;
    codeMemoryPtr[0]= opcode2;
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

void encodingRdRr(int Rd, int Rr, uint8_t opcode, uint8_t codeMemoryPtr[]){

  codeMemoryPtr[0] = opcode +  (( Rr >>4 ) <<1) + ( Rd >>4);
  if(Rr >= 16){
    codeMemoryPtr[1] = (Rd<<4)+ (Rr-16);
  }
  else{
  codeMemoryPtr[1] = (Rd<<4)+ Rr;
  }
}

void encodingBranch(uint8_t k, uint16_t opcode, uint8_t codeMemoryPtr[]){

  uint16_t temp = (k-1) & 0x7f;
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;
  *ptr = opcode | (temp<<3);
}

void encodingRdK8(uint8_t Rd , uint16_t K, uint16_t opCode, uint8_t codeMemoryPtr[]){
  uint16_t temp = (K & 0x00f0);
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;
  *ptr = opCode | (temp << 4 ) | (Rd-16)<<4 | (K&0x000f);
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
  for(int i = 0 ; i < 103; i++){
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
  //freeToken(token);
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

int ijmp(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //sleep mode

  encodingNoOperand(0x94,0x09,codeMemoryPtr);
  return TWO_BYTE;
}

int eijmp(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //indirect jump

  encodingNoOperand(0x94,0x19,codeMemoryPtr);
  return TWO_BYTE;
}

int icall(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //extended indirective jump

  encodingNoOperand(0x95,0x09,codeMemoryPtr);
  return TWO_BYTE;
}

int eicall(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //indirect call

  encodingNoOperand(0x95,0x19,codeMemoryPtr);
  return TWO_BYTE;
}

int ret(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //extended indirect call

  encodingNoOperand(0x95,0x08,codeMemoryPtr);
  return TWO_BYTE;
}

int reti(Tokenizer *tokenizer, uint8_t codeMemoryPtr[]){  //return from interupt

  encodingNoOperand(0x95,0x18,codeMemoryPtr);
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

int addRdRr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //add without carry

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x0c, codeMemoryPtr);

  return TWO_BYTE;
}

int adc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //add with carry

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x1c, codeMemoryPtr);
  return TWO_BYTE;
}

int sub(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //subrtact without carry

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x18, codeMemoryPtr);

  return TWO_BYTE;
}

int sbc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){   //subtract with carry

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x08, codeMemoryPtr);

  return TWO_BYTE;
}

int andRdRr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){  //logical AND

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x20, codeMemoryPtr);

  return TWO_BYTE;
}

int orRdRr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //logical OR

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x28, codeMemoryPtr);

  return TWO_BYTE;
}

int eor(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){  //exclusive or

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x24, codeMemoryPtr);

  return TWO_BYTE;
}

int mul(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //multiply unsigned

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x9c, codeMemoryPtr);

  return TWO_BYTE;
}

int mov(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //copy register

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x2c, codeMemoryPtr);

  return TWO_BYTE;
}

int cpse(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //compare skip if equal

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x10, codeMemoryPtr);

  return TWO_BYTE;
}

int cp(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ // compare

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x14, codeMemoryPtr);

  return TWO_BYTE;
}

int cpc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //compare with carry

  uint16_t values[2];    // values to store extraced value of Rd

  getRdRr(tokenizer, values ,R0,R31);
  encodingRdRr(values[0] , values[1] ,0x04, codeMemoryPtr);

  return TWO_BYTE;
}

int muls(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //multiply signed

  uint16_t values[2];    // values to store extraced value of operands

  getRdRr(tokenizer, values ,R16,R31);
  codeMemoryPtr[0]= 0x02;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 );

  return TWO_BYTE;
}

int mulsu(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //multiply signed with unsigned

  uint16_t values[2];    // values to store extraced value of operands

  getRdRr(tokenizer, values ,R16,R23);
  codeMemoryPtr[0]= 0x03;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 );

  return TWO_BYTE;
}

int fmul(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //fractional multiply unsigned

  uint16_t values[2];    // values to store extraced value of operands

  getRdRr(tokenizer, values ,R16,R23);
  codeMemoryPtr[0]= 0x03;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 ) + 0x08;

  return TWO_BYTE;
}

int fmuls(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //fractional multiply signed

  uint16_t values[2];    // values to store extraced value of operands

  getRdRr(tokenizer, values ,R16,R23);
  codeMemoryPtr[0]= 0x03;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 ) + 0x80;

  return TWO_BYTE;
}

int fmulsu(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //fractional multiply signed with unsigned

  uint16_t values[2];    // values to store extraced value of operands

  getRdRr(tokenizer, values ,R16,R23);
  codeMemoryPtr[0]= 0x03;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 ) + 0x88;

  return TWO_BYTE;
}

int breq(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if equal

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf001,codeMemoryPtr);

  return TWO_BYTE;
}

int brne(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if not equal

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf401,codeMemoryPtr);

  return TWO_BYTE;
}

int brcs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if carry set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf000,codeMemoryPtr);

  return TWO_BYTE;
}

int brcc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if carry cleared

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf400,codeMemoryPtr);

  return TWO_BYTE;
}

int brsh(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if carry set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf400,codeMemoryPtr);

  return TWO_BYTE;
}

int brlo(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if lower

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf000,codeMemoryPtr);

  return TWO_BYTE;
}

int brmi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if minus

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf002,codeMemoryPtr);

  return TWO_BYTE;
}

int brpl(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if plus

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf402,codeMemoryPtr);

  return TWO_BYTE;
}
int brge(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if greater

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf404,codeMemoryPtr);

  return TWO_BYTE;
}

int brlt(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if carry set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf004,codeMemoryPtr);

  return TWO_BYTE;
}

int brhs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if half carry set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf005,codeMemoryPtr);

  return TWO_BYTE;
}

int brhc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if half carry cleared

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf405,codeMemoryPtr);

  return TWO_BYTE;
}

int brts(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if T is set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf006,codeMemoryPtr);

  return TWO_BYTE;
}

int brtc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if T cleared

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf406,codeMemoryPtr);

  return TWO_BYTE;
}

int brvs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if overflow set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf003,codeMemoryPtr);

  return TWO_BYTE;
}

int brvc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if overflow set

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf403,codeMemoryPtr);

  return TWO_BYTE;
}

int brie(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if global interrupt enabled

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf007,codeMemoryPtr);

  return TWO_BYTE;
}

int brid(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //branch if global interrupt disabled

  uint16_t values[2];    // values to store extraced value of operands

  getK(tokenizer, values , -64 , 63);
  encodingBranch(values[0] , 0xf407,codeMemoryPtr);

  return TWO_BYTE;
}

int rjmp(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //brelative jump

  uint16_t values[2];    // values to store extraced value of operands

    getK(tokenizer, values , -2000 , 2000);
    uint16_t temp = (values[0]-1) & 0x0fff;

    uint16_t *ptr = (uint16_t *)codeMemoryPtr;
    *ptr =  0xc000 | (temp);

  return TWO_BYTE;
}

int rcall(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //relative call to subroutine

  uint16_t values[2];    // values to store extraced value of operands

    getK(tokenizer, values , -2000 , 2000);
    uint16_t temp = (values[0]-1) & 0x0fff;

    uint16_t *ptr = (uint16_t *)codeMemoryPtr;
    *ptr =  0xd000 | (temp);

  return TWO_BYTE;
}

int andi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //logical and with immediated

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x7000,codeMemoryPtr);

    return TWO_BYTE;
}

int ori(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //logical or with immediated

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x6000,codeMemoryPtr);

    return TWO_BYTE;
}

int subi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //subtract with immediated

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x5000,codeMemoryPtr);

    return TWO_BYTE;
}

int sbci(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //subtract immediated with carry

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x4000,codeMemoryPtr);

    return TWO_BYTE;
}

int ldi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //load immediated

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0xe000,codeMemoryPtr);

    return TWO_BYTE;
}

int cbr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //clear bits in register

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , ~values[1] , 0x7000,codeMemoryPtr);

    return TWO_BYTE;
}

int sbr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //set bits with register

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x6000,codeMemoryPtr);

    return TWO_BYTE;
}

int cpi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //compare with immediate

  uint16_t values[2];    // values to store extraced value of operands
  int minMax[4] = {16,31,0,255};

    getRdK8(tokenizer, values , minMax );
    encodingRdK8(values[0] , values[1] , 0x3000,codeMemoryPtr);

    return TWO_BYTE;
}

int adiw(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //add immediate to word

  Token *token = createNullToken();
  uint16_t values[2];    // values to store extraced value of operands
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;
  int minMax[4] = {24,30,0,63};

    getRdK8(tokenizer, values , minMax );
    int odd = ( values[0] % 2);
    if(odd >= 1){
      throwException(ERR_INVALID_REGISTER,token ,\
        "Only accept registers with the value of R24,26,28,30, but received '%d' ",values[0] );
    }else{
      *ptr = 0x9600 | (((values[0])-24)/2)<<4 | (values[1] & 0x30)<<2 | (values[1]&0x0f);
    }

    return TWO_BYTE;
}

int sbiw(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //add immediate to word

  Token *token = createNullToken();
  uint16_t values[2];    // values to store extraced value of operands
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;
  int minMax[4] = {24,30,0,63};

    getRdK8(tokenizer, values , minMax );
    int odd = ( values[0] % 2);
    if(odd >= 1){
      throwException(ERR_INVALID_REGISTER,token ,\
        "Only accept registers with the value of R24,26,28,30, but received '%d' ",values[0] );
    }else{
      *ptr = 0x9700 | (((values[0])-24)/2)<<4 | (values[1] & 0x30)<<2 | (values[1]&0x0f);
    }

    return TWO_BYTE;
}

int call(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //long call to a subroutine

  Token *token;
  uint16_t values[2];    // values to store extraced value of operands
  uint32_t *ptr = (uint32_t *)codeMemoryPtr;  //0x940e0000
  uint32_t longValues;

    longValues = getLongConstant(tokenizer , 0,4000000);
    *ptr = 0x940e0000 | (longValues&0x003f0000)<<3 | (longValues & 0x0001ffff);

    return FOUR_BYTE;
}

int jmp(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //long call to a subroutine

  Token *token;
  uint16_t values[2];    // values to store extraced value of operands
  uint32_t *ptr = (uint32_t *)codeMemoryPtr;  //0x940e0000
  uint32_t longValues;

    longValues = getLongConstant(tokenizer , 0,4000000);
    *ptr = 0x940c0000 | (longValues&0x003f0000)<<3 | (longValues & 0x0001ffff);

    return FOUR_BYTE;
}

int bset(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //set bit in SREG

  uint16_t value;
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    value = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9408 | (value&0x000f)<<4 ;

    return TWO_BYTE;
}

int bclr(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //clear bit in SREG

  uint16_t value;
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    value = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9488 | (value&0x000f)<<4 ;

    return TWO_BYTE;
}

int sbi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //set bit in i/o register

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[0] = getConstant(tokenizer, 0 , 31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9a00 | (values[0]&0x001f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int cbi(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //clear bit in i/o register

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[0] = getConstant(tokenizer, 0 , 31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9800 | (values[0]&0x001f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int bst(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Bit Store from Bit in Register to T Flag in SREG

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    getRd(tokenizer , values , 0 ,31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0xfa00 | (values[0]&0x001f)<<4 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int bld(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Bit Load from the T Flag in SREG to a Bit in Register.

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    getRd(tokenizer , values , 0 ,31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0xf800 | (values[0]&0x001f)<<4 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int sbrc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Skip if Bit in Register is Cleared

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    getRd(tokenizer , values , 0 ,31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0xfc00 | (values[0]&0x001f)<<4 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int sbrs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Skip if Bit in Register is Set

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    getRd(tokenizer , values , 0 ,31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0xfe00 | (values[0]&0x001f)<<4 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int sbic(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Skip if Bit in I/O Register is Cleared

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[0] = getConstant(tokenizer, 0 , 31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9900 | (values[0]&0x001f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int sbis(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Skip if Bit in I/O Register is Set

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[0] = getConstant(tokenizer, 0 , 31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer, 0 , 7);
    *ptr = 0x9b00 | (values[0]&0x001f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int brbc(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Branch if Bit in SREG is Cleared

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[1] = getConstant(tokenizer, 0 , 7);
    getNextTokenAndVerify(tokenizer,",");
    getK(tokenizer,values,-64,63);
    *ptr = 0xf400 | ((values[0]-1)&0x007f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int brbs(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Branch if Bit in SREG is set

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[1] = getConstant(tokenizer, 0 , 7);
    getNextTokenAndVerify(tokenizer,",");
    getK(tokenizer,values,-64,63);
    *ptr = 0xf000 | ((values[0]-1)&0x007f)<<3 | (values[1]&0x0007) ;

    return TWO_BYTE;
}

int in(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //Load an I/O Location to Register

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    getRd(tokenizer,values , 0 ,31);
    getNextTokenAndVerify(tokenizer,",");
    values[1] = getConstant(tokenizer,0,63);
    *ptr = 0xb000 | (values[0]&0x001f)<<4 | (values[1]&0x0030)<<5 | values[1]&0x000f ;

    return TWO_BYTE;
}

int out(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //store an I/O Location to Register

  uint16_t values[2];
  uint16_t *ptr = (uint16_t *)codeMemoryPtr;

    values[1] = getConstant(tokenizer,0,63);
    getNextTokenAndVerify(tokenizer,",");
    getRd(tokenizer,values , 0 ,31);
    *ptr = 0xb800 | (values[0]&0x001f)<<4 | (values[1]&0x0030)<<5 | values[1]&0x000f ;

    return TWO_BYTE;
}

/*int ld(Tokenizer *tokenizer , uint8_t codeMemoryPtr[]){ //load indirect data

  uint16_t values[1];    // values to store extraced value of operands

  values[0] = getRegister(tokenizer,R0,R31);
  codeMemoryPtr[0]= 0x03;
  codeMemoryPtr[1]= (values[0]<<4) + (values[1] -16 ) + 0x88;

  return TWO_BYTE;
}*/

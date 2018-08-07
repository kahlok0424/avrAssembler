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

char *encodingRd(int Rd){

}

void inc(Tokenizer *tokenizer , uint8_t **codeMemoryPtr){

  uint16_t values[1];    // values to store extraced value of Rd
  Token *token;
  uint8_t ptr[4] ;
  //ptr = *codeMemoryPtr;

  getRd(tokenizer, values ,R0,R31);

  ptr[0] = 0x9;
  int result = 0;
  result = values[0];
  //return result;
}

void test_binary(void){
  int i = 0b00111;
  //printf("\nbinary number i = %d\n", i );
}

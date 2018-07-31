#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getoperand.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "Token.h"
#include "Error.h"
#include "assembler.h"

int adc(char *line){
  Tokenizer *tokenizer;
  tokenizer = createTokenizer(line);
  uint16_t values[1];    // values to store extraced value of Rd

  getRd(tokenizer ,values);          //last modified : trying to make sure correct values get returned
  printf("test : " , values[0]);
  int result = 0;
  result = values[0];
  return result;
}

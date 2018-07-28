#include <stdio.h>
#include "SimpleArithmetic.h"
#include "Error.h"
#include "Exception.h"

int operateOn2Numbers(Tokenizer *tokenizer) {
  Token *token;
  int v1, v2;
  char operator;

  token = getToken(tokenizer);
  if(token->type != TOKEN_INTEGER_TYPE)
    throwException(ERR_EXPECTING_INTEGER, token, "The first element is not integer");
  v1 = ((IntegerToken *)token)->value;
  freeToken(token);

  token = getToken(tokenizer);
  if(token->type != TOKEN_OPERATOR_TYPE)
    throwException(ERR_EXPECTING_OPERATOR, token, "The second element is not operator");
  operator = ((OperatorToken *)token)->str[0];
  freeToken(token);

  token = getToken(tokenizer);
  if(token->type != TOKEN_INTEGER_TYPE)
    throwException(ERR_EXPECTING_INTEGER, token, "The third element is not integer");
  v2 = ((IntegerToken *)token)->value;
  freeToken(token);

  switch(operator) {
    case '+':
      v1 = v1 + v2;
      break;
    case '-':
      v1 = v1 - v2;
      break;
    case '*':
      v1 = v1 * v2;
      break;
    case '/':
      v1 = v1 / v2;
      break;
    default:
      throwException(ERR_INVALID_OPERATOR, NULL, "Do not understand '%c' operator", operator);
  }

  return v1;
}
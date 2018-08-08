#include "unity.h"
#include "assembler.h"
#include "getoperand.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void test_convertToLowerCase_given_ABC_epxect_abc(void){
  char *line = "ABC";
  TEST_ASSERT_EQUAL_STRING("abc", convertToLowerCase(line));
}

void test_assembler_INC_given_R16_expect_opcode(void)
{
  char *line = "R17";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];

  tokenizer = createTokenizer(line);
  inc(tokenizer , codeMemoryPtr);
  printf("code : %x \n" , codeMemoryPtr[0]);
  printf("code 1: %x \n" , codeMemoryPtr[1]);
  Try{
  TEST_ASSERT_EQUAL(0x9f13,codeMemoryPtr[0]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_getToken_given_random_line(void){
  char *line = "inc R12 +++";
  Tokenizer *tokenizer;
  Token *token;

  tokenizer = createTokenizer(line);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("inc",token->str);
  freeToken(token);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("R12",token->str);
  freeToken(token);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("+",token->str);
  freeToken(token);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("+",token->str);
  freeToken(token);
}

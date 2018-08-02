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

void test_getTokenAndVerify_given_comma_expect_correct(void){
  char *line = ",";
  Tokenizer *tokenizer;
  Token *token;

  Try{
  tokenizer = createTokenizer(line);
  getNextTokenAndVerify(tokenizer,",");
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_getTokenAndVerify_given_semicolum_expect_correct(void){
  char *line = ";";
  Tokenizer *tokenizer;
  Token *token;

  Try{
  tokenizer = createTokenizer(line);
  getNextTokenAndVerify(tokenizer,";");
  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE,token->type);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_getTokenAndVerify_given_plus_expect_wrong_operator(void){
  char *line = "+";
  Tokenizer *tokenizer;
  Token *token;

  Try{
  tokenizer = createTokenizer(line);
  getNextTokenAndVerify(tokenizer,";");
  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE,token->type);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_getTokenAndVerify_given_3_plus_expect_wrong_operator(void){
  char *line = "+++";
  Tokenizer *tokenizer;
  Token *token;

  Try{
  tokenizer = createTokenizer(line);
  getNextTokenAndVerify(tokenizer,"+");
  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE,token->type);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_INC_given_R16_expect_opcode(void)
{
  char *line = "inc R16";
  Token *token;
  Tokenizer *tokenizer;

  tokenizer = createTokenizer(line);
  test_binary();
  Try{
  TEST_ASSERT_EQUAL(16,inc(line));
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

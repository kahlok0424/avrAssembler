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

void test_sec_expect_correct_assembler(void){
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];

  sec(codeMemoryPtr);
  printf("code  la: %x \n" , codeMemoryPtr[0]  );
}

void test_encodingRd_given_inc_opcode_expext_correctly_encoded(void){
  uint8_t opCode1 = 0x94;
  uint8_t opCode2 = 0x03;
  int Rd = 16;
  uint8_t *memoryPtr;

  memoryPtr = encodingRd(Rd , opCode1 , opCode2);
  //printf("lala : %x " , memoryPtr);
  //TEST_ASSERT_EQUAL(0x9403 , memoryPtr );
}

void test_assembler_INC_given_R16_expect_opcode(void)
{
  char *line = "R17";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t **codeMemoryPtr;

  tokenizer = createTokenizer(line);
  inc(tokenizer , codeMemoryPtr);
  printf("code : %x \n" , *codeMemoryPtr  );
  //printf("code 1: %x \n" , codeMemoryPtr[1]);
  Try{
  TEST_ASSERT_EQUAL(0x9f13, *codeMemoryPtr);
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

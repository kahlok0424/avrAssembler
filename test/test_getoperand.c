#include "unity.h"
#include "getoperand.h"
#include "Tokenizer.h"
#include "Token.h"

void setUp(void)
{
}

void tearDown(void)
{
}

CEXCEPTION_T ex;

void test_getRd_given_r12_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("r12");

  getRd(tokenizer, values);
  TEST_ASSERT_EQUAL(12,values[0]);
}

void test_getRd_given_R7_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R7");

  getRd(tokenizer, values);
  TEST_ASSERT_EQUAL(7,values[0]);
}

void test_getRd_given_z15_expect_exception_incorrect_operand(void)
{
  char *operands = "z45";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  //TEST_ASSERT_EQUAL(12,values[0]);
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_r45_expect_exception_beyond_limit(void)
{
  char *operands = "r45";
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_ASSERT_EQUAL(12,values[0]);
}

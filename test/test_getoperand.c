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
  Try {
  getRd(tokenizer, values);
  TEST_ASSERT_EQUAL(12,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_R7_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R7");

  Try {
  getRd(tokenizer, values);
  TEST_ASSERT_EQUAL(7,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_z15_expect_exception_incorrect_identifier(void)
{
  char *operands = "z15";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_r45_expect_exception_beyond_limit(void)
{
  char *operands = "r45";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_r_negative_one_expect_exception_incorrect_identifier(void)
{
  char *operands = "r-1";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_rbbb2_expect_exception_incorrect_identifier(void)
{
  char *operands = "rbbb2";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_2r_expect_exception_incorrect_integer(void)
{
  char *operands = "2r";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r2_r4_expect_extract_correctly(void)
{
  uint16_t values[2];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("r2 , r4");
  Try {
  getRdRr(tokenizer, values);
  TEST_ASSERT_EQUAL(2,values[0]);
  TEST_ASSERT_EQUAL(4,values[1]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_R7_R8_expect_extract_correctly(void)
{
  uint16_t values[2];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R7, R8");

  Try {
  getRdRr(tokenizer, values);
  TEST_ASSERT_EQUAL(7,values[0]);
  TEST_ASSERT_EQUAL(8,values[1]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_z15_r17_expect_exception_incorrect_identifier(void)
{
  char *operands = "z15 , r17";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r5_x1_expect_exception_incorrect_identifier(void)
{
  char *operands = "r5 , x1";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r45_r10_expect_exception_beyond_limit(void)
{
  char *operands = "r45,r10";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r10_r45_expect_exception_beyond_limit(void)
{
  char *operands = "r10,r45";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r_negative_one_r2_expect_exception_incorrect_identifier(void)
{
  char *operands = "r-1 , r2";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_rbbb2_r4_expect_exception_incorrect_identifier(void)
{
  char *operands = "rbbb2 , r4";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_2r_r6_expect_exception_incorrect_integer(void)
{
  char *operands = "2r , r6";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

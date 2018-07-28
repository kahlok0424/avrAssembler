#include <stdlib.h>
#include <errno.h>
#include "unity.h"
#include "SimpleArithmetic.h"
#include "Common.h"
#include "Error.h"
#include "Token.h"
#include "Tokenizer.h"
#include "CException.h"
#include "Exception.h"

void setUp(void) {}

void tearDown(void) {}

void test_operateOn2Numbers_with_multiplication() {
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  int result;

  // Run test
  Try {
    tokenizer = createTokenizer(" 23 * 78 ");
    result = operateOn2Numbers(tokenizer);
    printf("%s = %d\n", tokenizer->str, result);
    TEST_ASSERT_EQUAL(23 * 78, result);
  } Catch(e) {
    // Catch and display exception if it has been thrown
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_operateOn2Numbers_with_subtracion() {
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  int result;

  // Run test
  Try {
    tokenizer = createTokenizer(" 12 - 765678 ");
    result = operateOn2Numbers(tokenizer);
    printf("%s = %d\n", tokenizer->str, result);
    TEST_ASSERT_EQUAL(12 - 765678, result);
  } Catch(e) {
    // Catch and display exception if it has been thrown
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_operateOn2Numbers_with_divide() {
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  int result;

  // Run test
  Try {
    tokenizer = createTokenizer(" 456/   2 ");
    result = operateOn2Numbers(tokenizer);
    printf("%s = %d\n", tokenizer->str, result);
    TEST_ASSERT_EQUAL(456/2, result);
  } Catch(e) {
    // Catch and display exception if it has been thrown
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}
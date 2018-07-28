#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "unity.h"
#include "Common.h"
#include "Token.h"
#include "Error.h"
#include "Tokenizer.h"
#include "CException.h"
#include "Exception.h"

CEXCEPTION_T ex;

void setUp(void) {}

void tearDown(void) {}


void test_skipWhiteSpaces_given_empty_string_expect_to_skip_till_end_of_string() {
  char *endPtr = skipWhiteSpaces("               ");

  TEST_ASSERT_EQUAL(0, *endPtr);
}

void test_skipWhiteSpaces_given____Hello_string_expect_to_skip_till_H() {
  char *endPtr = skipWhiteSpaces("   Hello   ");

  TEST_ASSERT_EQUAL('H', *endPtr);
}

void test_getToken_given_nothing_expect_NullToken() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("     ");
  token = getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(token);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void test_getToken_given_123_expect_Integer_Token_123() {
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 123");
  intToken = (IntegerToken *)getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(intToken);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
  TEST_ASSERT_EQUAL(123, intToken->value);
  TEST_ASSERT_EQUAL_STRING("123", intToken->str);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  freeToken(intToken);
  freeTokenizer(tokenizer);
}

void test_getToken_given_0xface_expect_Integer_Token_0xface() {
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 0xface ");
  intToken = (IntegerToken *)getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(intToken);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
  TEST_ASSERT_EQUAL_STRING("0xface", intToken->str);
  TEST_ASSERT_EQUAL(0xface, intToken->value);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  freeToken(intToken);
  freeTokenizer(tokenizer);
}

void test_getToken_given_00xface_expect_ERR_INVALID_INTEGER_exception() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("   00xface + bad_boy + 456 ");

  Try {
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_INTEGER exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_INTEGER, ex->errorCode);
  }
}

void test_getToken_given_config_set_to_recognize_dollar_sign_23acbdef_expect_return_23acbdef() {
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" $23acbdef ");
  configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);

  Try {
    intToken = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(intToken);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
    TEST_ASSERT_EQUAL_STRING("$23acbdef", intToken->str);
    TEST_ASSERT_EQUAL(0x23acbdef, intToken->value);
    TEST_ASSERT_EQUAL(10, tokenizer->index);
    freeToken(intToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_config_set_not_to_recognize_dollar_sign_bad_expect_return_dollar_sign_operator_token() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" $bad ");

  Try {
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("$", token->str);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    freeToken(token);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_0y12ab_expect_ERR_INVALID_INTEGER_exception() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("          0y12ab  <- this is invalid ");
  Try {
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_INTEGER exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_EQUAL(ERR_INVALID_INTEGER, ex->errorCode);
  }
}

void test_getToken_given_934minus_expect_integer_token_934_to_be_returned() {
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 934-  ");
  Try {
    intToken = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(intToken);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
    TEST_ASSERT_EQUAL_STRING("934", intToken->str);
    TEST_ASSERT_EQUAL(934, intToken->value);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    freeToken(ex->data);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
  freeTokenizer(tokenizer);
}

void test_getToken_given_0x900d_comma_expect_integer_token_0x900d_to_be_returned() {
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("  0x900d,  ");
  Try {
    intToken = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(intToken);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
    TEST_ASSERT_EQUAL_STRING("0x900d", intToken->str);
    TEST_ASSERT_EQUAL(0x900d, intToken->value);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    freeToken(ex->data);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
  freeTokenizer(tokenizer);
}

void test_getToken_given_456abc_expect_ERR_INVALID_INTEGER_exception() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer(" 456abc  ballon ");

  Try {
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_INTEGER exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    freeToken(ex->data);
    TEST_ASSERT_EQUAL(ERR_INVALID_INTEGER, ex->errorCode);
  }
  freeTokenizer(tokenizer);
}

void test_getToken_given_ali_expect_Identifier_Token_ali() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("   ali  ");
  token = getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(token);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("ali", token->str);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void test_getToken_given_alladin123456_expect_Identifier_Token_alladin123456() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("   alladin123456 123+67  ");
  token = getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(token);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("alladin123456", token->str);
  TEST_ASSERT_EQUAL(16, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void test_getToken_given_babuplus_expect_Identifier_Token_babu() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  tokenizer = createTokenizer("   babu+   ");
  token = getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(token);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING("babu", token->str);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
  freeToken(token);
  freeTokenizer(tokenizer);
}

void test_getToken_given_some_string_expect_String_Token_to_be_returned() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  \" Yada@#$%^&*()_=|[]{}//<>,.\" ");
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING(" Yada@#$%^&*()_=|[]{}//<>,.", token->str);
    TEST_ASSERT_EQUAL(31, tokenizer->index);      // !!!This one fails!!! Please fix it
    freeToken(token);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_greetings_string_without_closing_quotation_mark_expect_ERR_INVALID_STRING_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  \"greetings  !! !  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_123dot567_expect_float_123dot567() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  123.567  ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("123.567", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 123.567, floatToken->value);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_4dot6_and_plus_expect_float_4dot6() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  4.6+  ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("4.6", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 4.6, floatToken->value);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_1dot98765e_plus_12_expect_float_1dot98765e12() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  1.98765e+12  ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("1.98765e+12", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 1.98765e12, floatToken->value);
    TEST_ASSERT_EQUAL(13, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_189dot_expect_float_189dot0() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  189. ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("189.", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 189.0, floatToken->value);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_987dote2_expect_float_987dot0e2() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("   987.e2 ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("987.e2", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 987.0e2, floatToken->value);
    TEST_ASSERT_EQUAL(9, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}


void test_getToken_given_8dote_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  8.e ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_4dote_plus_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  4.e+abc ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_2dot3456e_plus_plus_8_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  1.98765e++8  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_8dot43210e_minus_minus_60_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  8.43210e--60 ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_8dot43210e_minus_minus_6_minus_56_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  FloatToken *floatToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  8.43210e-6-56 ");
    floatToken = (FloatToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(floatToken);
    TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, floatToken->type);
    TEST_ASSERT_EQUAL_STRING("8.43210e-6", floatToken->str);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-7, 8.43210e-6, floatToken->value);
    TEST_ASSERT_EQUAL(12, tokenizer->index);
    freeToken(floatToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_10dot1234e_mul_45_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  10.1234e*45  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_5dot4567e_minus_4e5_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  5.4675e-4e5  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_56dot78dot90_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  56.78.90  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_3dot43526abc_expect_ERR_INVALID_FLOAT_exception_to_be_thrown() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  3.43526abc  ");
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expected ERR_INVALID_FLOAT exception to be thrown, but none received.");
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_dot_e5_expect_dot_operator_token_to_be_returned() {
  OperatorToken *opToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("  .e5 = 0.e+5 ");
    opToken = (OperatorToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(opToken);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, opToken->type);
    TEST_ASSERT_EQUAL_STRING(".", opToken->str);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    freeToken(opToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_dot_jynx_expect_dot_operator_token_to_be_returned() {
  OperatorToken *opToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("   .jynx ");
    opToken = (OperatorToken *)getToken(tokenizer);

    TEST_ASSERT_NOT_NULL(opToken);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, opToken->type);
    TEST_ASSERT_EQUAL_STRING(".", opToken->str);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    freeToken(opToken);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_plus_equal_minus_symbols_expect_operator_tokens_to_be_returned() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer(" +=  - ");
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("+", token->str);
    TEST_ASSERT_EQUAL(2, tokenizer->index);
    freeToken(token);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("=", token->str);
    TEST_ASSERT_EQUAL(3, tokenizer->index);
    freeToken(token);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("-", token->str);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    freeToken(token);
    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_r23_comma_r6_expect_those_tokens_to_be_returned() {
  Token *token = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer(" r23, r6  ");
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("r23", token->str);
    TEST_ASSERT_EQUAL(4, tokenizer->index);
    freeToken(token);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING(",", token->str);
    TEST_ASSERT_EQUAL(5, tokenizer->index);
    freeToken(token);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("r6", token->str);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    freeToken(token);

    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_getToken_given_r22_colon_dollar_sign_abc123_expect_those_tokens_to_be_returned(void) {
  Token *token = NULL;
  IntegerToken *intToken = NULL;
  Tokenizer *tokenizer = NULL;

  Try {
    tokenizer = createTokenizer("   r45 :  $abc123  ");
    configureTokenizer(tokenizer, TOKENIZER_DOLLAR_SIGN_HEX);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING("r45", token->str);
    TEST_ASSERT_EQUAL(6, tokenizer->index);
    freeToken(token);

    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, token->type);
    TEST_ASSERT_EQUAL_STRING(":", token->str);
    TEST_ASSERT_EQUAL(8, tokenizer->index);
    freeToken(token);

    intToken = (IntegerToken *)getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(intToken);
    TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
    TEST_ASSERT_EQUAL_STRING("$abc123", intToken->str);
    TEST_ASSERT_EQUAL_HEX(0xabc123, intToken->value);
    TEST_ASSERT_EQUAL(17, tokenizer->index);
    freeToken(intToken);

    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    // Should return NULL token because no more operator
    token = getToken(tokenizer);
    TEST_ASSERT_NOT_NULL(token);
    TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
    freeToken(token);
    freeTokenizer(tokenizer);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
    TEST_FAIL_MESSAGE("Do not expect any exception to be thrown.");
  }
}

void test_error_throwing(void) {
  Tokenizer *tokenizer;
  Token *token;
  Try {
    tokenizer = createTokenizer(" 45 abu bakar ");
    token = getToken(tokenizer);
    throwException(ERR_SYSTEM_ERROR, token, "Just for fun: Do not expect a number here: %s", token->str);
  } Catch(ex) {
    dumpTokenErrorMessage(ex, 1);
  }
}


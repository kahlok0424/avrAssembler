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

void test_getRegister_given_r12_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("r12");
  Try {
  values[0] = getRegister(tokenizer, R0,R31);
  TEST_ASSERT_EQUAL(12,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_R7_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R7");

  Try {
  values[0] = getRegister(tokenizer, R0,R31);
  TEST_ASSERT_EQUAL(7,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_r18_limit_16_to31_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("r18");

  Try {
  values[0] = getRegister(tokenizer, R16,R31);
  TEST_ASSERT_EQUAL(18,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_R7_limit_16_to_31_expect_extract_beyond_limit(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R7");

  Try {
  values[0] = getRegister(tokenizer, R16,R31);
  //TEST_ASSERT_EQUAL(18,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_r45_expect_exception_beyond_limit(void)
{
  char *operands = "r45";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  values[0] = getRegister(tokenizer, R0,R31);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_R30_limit_0_to_16_expect_extract_beyond_limit(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("R30");

  Try {
  values[0] = getRegister(tokenizer, R0,R16);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_k15_expect_exception_incorrect_identifier(void)
{
  char *operands = "k15";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  values[0] = getRegister(tokenizer, R0,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_r_negative_one_expect_exception_incorrect_identifier(void)
{
  char *operands = "r-1";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  values[0] = getRegister(tokenizer, R0,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_rbb9_expect_exception_incorrect_identifier(void)
{
  char *operands = "rbb9";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  values[0] = getRegister(tokenizer, R0,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRegister_given_7r_expect_exception_incorrect_integer(void)
{
  char *operands = "7r";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  values[0] = getRegister(tokenizer, R0,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
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
  char *line = "++";
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

//old test for old functions
void test_getRd_given_r12_expect_extract_correctly(void)
{
  uint16_t values[1];
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer("r12");
  Try {
  getRd(tokenizer, values , R0,R31);
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
  getRd(tokenizer, values, R0,R31);
  TEST_ASSERT_EQUAL(7,values[0]);
  }Catch(ex){
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRd_given_r1_limit_R16_to_R31_expect_exception_beyond_limit(void)
{
  char *operands = "r1";
  uint16_t values[1];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRd(tokenizer, values, R16,R31);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
  }Catch(ex) {
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

  getRd(tokenizer, values, R0,R31);
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

  getRd(tokenizer, values, R0,R31);
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

  getRd(tokenizer, values, R0,R31);
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

  getRd(tokenizer, values, R0,R31);
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

  getRd(tokenizer, values, R0,R31);
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
  getRdRr(tokenizer, values , R0 ,R31);
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
  getRdRr(tokenizer, values ,R0 , R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
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

  getRdRr(tokenizer, values , R0, R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
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

  getRdRr(tokenizer, values , R0 ,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_IDENTIFIER exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r4_equal_r5_expect_exception_invalid_operator(void)
{
  char *operands = "r4 = r5";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values , R0 ,R31);
  TEST_FAIL_MESSAGE("Expected ERR_INVALID_OPERATOR exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getRdRr_given_r1_A_r2_expect_exception_expecting_operator(void)
{
  char *operands = "r1 A r2";
  uint16_t values[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);

  getRdRr(tokenizer, values , R0 ,R31);
  TEST_FAIL_MESSAGE("Expected ERR_EXPECTING_OPERATOR exception to be thrown, but none received.");
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getK_given_5_expect_encoded_correctly(void)
{
  char *operands = "pc+5";
uint16_t pc[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);
  getK(tokenizer,pc );
  TEST_ASSERT_EQUAL(5 ,pc[0] );
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getK_given_negative_20_expect_correct(void)
{
  char *operands = "pc-20";
  uint16_t pc[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);
  getK(tokenizer,pc);
  TEST_ASSERT_EQUAL(65516,pc[0] );
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getK_given_negative_100_expect_exception_thrown(void)
{
  char *operands = "pc-100";
  uint16_t pc[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);
 getK(tokenizer,pc);
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

void test_getK_given_plus_expect_exception_thrown(void)
{
  char *operands = "+";
  uint16_t pc[2];

  Try {
  Tokenizer *tokenizer = NULL;
  tokenizer = createTokenizer(operands);
  getK(tokenizer,pc);
  //TEST_ASSERT_EQUAL(5 ,pc );
  }Catch(ex) {
  dumpTokenErrorMessage(ex, 1);
  }
}

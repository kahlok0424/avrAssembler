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

  //sec(codeMemoryPtr);
  //printf("code  la: %x \n" , codeMemoryPtr[0]  );
}

void test_encodingRd_given_opcode_expext_correctly_encoded(void){
  uint8_t opCode1 = 0x12;
  uint8_t opCode2 = 0x34;
  int Rd = 16;
  uint8_t memoryPtr[1];

  encodingRd(Rd , opCode1,opCode2 , memoryPtr );
  TEST_ASSERT_EQUAL(0x13 , memoryPtr[0]);
  TEST_ASSERT_EQUAL(0x34 , memoryPtr[1]);
}

void test_assembleOneInstruction_given_INC_R7_expect_assemble_correctly(void)
{
  char *line = "inc R7";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;


  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x7394,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2 , byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_DEC_r10_expect_assemble_correctly(void)
{
  char *line = "DEC r10";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;


  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xaa94,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2 , byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_SWAP_r9_expect_assemble_correctly(void)
{
  char *line = "Swap r9";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;


  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x9294,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2 , byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_INC_given_R7_expect_assembler_correctly(void)
{
  char *line = "R7";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = inc(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x73, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_INC_given_R17_expect_assembler_correctly(void)
{
  char *line = "R17";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = inc(tokenizer , codeMemoryPtr);
  //printf("code : %x \n" , codeMemoryPtr[0] );
  //printf("code 1: %x \n" , codeMemoryPtr[1]);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x13, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_DEC_given_R01_expect_assembler_correctly(void)
{
  char *line = "R01";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = dec(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x1a, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}


void test_assembler_DEC_given_R20_expect_assembler_correctly(void)
{
  char *line = "R20";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = dec(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x4a, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_COM_given_R0_expect_assembler_correctly(void)
{
  char *line = "R0";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = com(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x00, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_COM_given_R21_expect_assembler_correctly(void)
{
  char *line = "R21";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = com(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x50, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_NEG_given_R0_expect_assembler_correctly(void)
{
  char *line = "R0";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = neg(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x01, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_NEG_given_R21_expect_assembler_correctly(void)
{
  char *line = "R21";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = neg(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x51, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_PUSH_given_R1_expect_assembler_correctly(void)
{
  char *line = "R1";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = push(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x92, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x1f, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_PUSH_given_R26_expect_assembler_correctly(void)
{
  char *line = "R26";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = push(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x93, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xaf, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_POP_given_R2_expect_assembler_correctly(void)
{
  char *line = "R2";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = pop(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x90, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x2f, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_POP_given_R27_expect_assembler_correctly(void)
{
  char *line = "R27";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = pop(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x91, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xbf, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_LSR_given_R8_expect_assembler_correctly(void)
{
  char *line = "R8";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = lsr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x86, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_LSR_given_R28_expect_assembler_correctly(void)
{
  char *line = "R28";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = lsr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xc6, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_ASR_given_R8_expect_assembler_correctly(void)
{
  char *line = "R8";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = asr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x85, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_ASR_given_R28_expect_assembler_correctly(void)
{
  char *line = "R28";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = asr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xc5, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_SWAP_given_R10_expect_assembler_correctly(void)
{
  char *line = "R10";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = swap(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xa2, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_SWAP_given_R30_expect_assembler_correctly(void)
{
  char *line = "R30";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = swap(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x95, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0xe2, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_LSL_given_R3_expect_assembler_correctly(void)
{
  char *line = "R3";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = lsl(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x0c, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x33, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_LSL_given_R19_expect_assembler_correctly(void)
{
  char *line = "R19";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = lsl(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x0f, codeMemoryPtr[0]);
  TEST_ASSERT_EQUAL(0x33, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_LSL_given_R29_expect_assembler_correctly(void)
{
  char *line = "R29";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t *codeMemoryPtr[4];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = lsl(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0xdd0f, *(uint16_t *)codeMemoryPtr);
  //TEST_ASSERT_EQUAL(0xdd, codeMemoryPtr[1]);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_CLR_given_R9_expect_assembler_correctly(void)
{
  char *line = "R9";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = clr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x9924, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_CLR_given_R19_expect_assembler_correctly(void)
{
  char *line = "R19";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = clr(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x3327, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_TST_given_R9_expect_assembler_correctly(void)
{
  char *line = "R2";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = tst(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x2220, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_TST_given_R19_expect_assembler_correctly(void)
{
  char *line = "R23";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = tst(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x7723, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_ROL_given_R9_expect_assembler_correctly(void)
{
  char *line = "R8";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = rol(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x881c, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_ROL_given_R19_expect_assembler_correctly(void)
{
  char *line = "R28";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = rol(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0xcc1f, *(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_SER_given_R31_expect_encoed_correctly(void)
{
  char *line = "R31";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;


  Try{
  tokenizer = createTokenizer(line);
  byte_number = ser(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xffef ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_SER_given_R20_expect_encoed_correctly(void)
{
  char *line = "R20";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;


  Try{
  tokenizer = createTokenizer(line);
  byte_number = ser(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x4fef ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_SER_given_R6_expect_exception_thrown(void)
{
  char *line = "R6";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = ser(tokenizer ,*(uint16_t *)codeMemoryPtr);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
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

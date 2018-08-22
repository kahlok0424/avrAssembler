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

void test_encodingNoOperand_given_45_67_expect_encoded_correctly(void){
  uint8_t opCode1 = 0x45;
  uint8_t opCode2 = 0x67;
  uint8_t memoryPtr[1];

  encodingNoOperand(opCode1,opCode2 , memoryPtr );
  TEST_ASSERT_EQUAL(0x4567,*(uint16_t *)memoryPtr);
}

void test_encodingRd_given_opcode_expect_correctly_encoded(void){
  uint8_t opCode1 = 0x12;
  uint8_t opCode2 = 0x34;
  int Rd = 16;
  uint8_t memoryPtr[1];

  encodingRd(Rd , opCode1,opCode2 , memoryPtr );
  TEST_ASSERT_EQUAL(0x13 , memoryPtr[0]);
  TEST_ASSERT_EQUAL(0x34 , memoryPtr[1]);
}

void test_encodingRdRr_given_rdrd_opcode_expect_correctly_encoded(void){
  uint8_t opCode = 0x0c;
  int Rd = 4;
  int Rr = 25;
  uint8_t memoryPtr[1];

  encodingRdRr(Rd ,Rr , opCode , memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0x490e ,*(uint16_t *)memoryPtr);
}

void test_encodingRdRr_given_r18_r6_opcode_expect_correctly_encoded(void){
  uint8_t opCode = 0x0c;
  int Rd = 18;
  int Rr = 6;
  uint8_t memoryPtr[1];

  encodingRdRr(Rd , Rr , opCode , memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0x260d ,*(uint16_t *)memoryPtr);
}

void test_encodingRdRr_given_r2_r8_opcode_expect_correctly_encoded(void){
  uint8_t opCode = 0x00;
  int Rd = 2;
  int Rr = 8;
  uint8_t memoryPtr[1];

  encodingRdRr(Rd , Rr , opCode , memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0x2800 ,*(uint16_t *)memoryPtr);
}

void test_encodingRdRr_given_r30_r31_opcode_expect_correctly_encoded(void){
  uint8_t opCode = 0x20;
  int Rd = 30;
  int Rr = 31;
  uint8_t memoryPtr[1];

  encodingRdRr(Rd , Rr , opCode , memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0xef23 ,*(uint16_t *)memoryPtr);
}

void test_encodingBranch_given_2_opcode_expect_correctly_encoded(void){
  int k = 2;
  uint8_t memoryPtr[1];

  encodingBranch(k ,0xf000, memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0xf008 ,*(uint16_t *)memoryPtr);
}

void test_encodingBranch_given_negative_50_opcode_expect_correctly_encoded(void){
  uint16_t k = -9;
  uint8_t memoryPtr[2];

  encodingBranch(k , 0xf002, memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0xf3b2 ,*(uint16_t *)memoryPtr);
}

void test_encodingBranch_given_negative_7_opcode_expect_correctly_encoded(void){
  uint8_t opCode1 = 0xf0;
  uint8_t opCode2 = 0x01;
  uint16_t k = -7;
  uint8_t memoryPtr[2];

  encodingBranch(k , 0xf001, memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0xf3c1 ,*(uint16_t *)memoryPtr);
}

void test_encodingRdK8_given_R20_55_opcode_expect_correctly_encoded(void){
  uint8_t memoryPtr[2];

  encodingRdK8( 20 , 0x55, 0x7000, memoryPtr );
  TEST_ASSERT_EQUAL_HEX16(0x7545 ,*(uint16_t *)memoryPtr);  //7545
}

void test_assembler_sec_expect_assembler_correctly(void)
{
  char *line = "sec";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x9408,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_clc_expect_assembler_correctly(void)
{
  char *line = "clc";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9488,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sen_expect_assembler_correctly(void)
{
  char *line = "sen";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9428,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cln_expect_assembler_correctly(void)
{
  char *line = "cln";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94a8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sez_expect_assembler_correctly(void)
{
  char *line = "sez";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9418,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_clz_expect_assembler_correctly(void)
{
  char *line = "clz";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9498,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sei_expect_assembler_correctly(void)
{
  char *line = "sei";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9478,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cli_expect_assembler_correctly(void)
{
  char *line = "cli ";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94f8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_ses_expect_assembler_correctly(void)
{
  char *line = "ses ";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9448,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cls_expect_assembler_correctly(void)
{
  char *line = " cls";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94c8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_set_expect_assembler_correctly(void)
{
  char *line = " set";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9468,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_clt_expect_assembler_correctly(void)
{
  char *line = "clt";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94e8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_seh_expect_assembler_correctly(void)
{
  char *line = "seh";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9458,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_clh_expect_assembler_correctly(void)
{
  char *line = "clh";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x94d8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_nop_expect_assembler_correctly(void)
{
  char *line = "nop";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x0000,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sleep_expect_assembler_correctly(void)
{
  char *line = "sleep ";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL(0x9588,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneStruction_ijmp_expect_assemble_correctly(void)
{
  char *line = "ijmp";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9409 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_eijmp_expect_assemble_correctly(void)
{
  char *line = "eijmp";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9419 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_icall_expect_assemble_correctly(void)
{
  char *line = "icall";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9509 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_eicall_expect_assemble_correctly(void)
{
  char *line = "eicall";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9519 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_ret_expect_assemble_correctly(void)
{
  char *line = "ret";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9508 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_reti_expect_assemble_correctly(void)
{
  char *line = "reti";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9518 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembler_wdr_expect_assembler_correctly(void)
{
  char *line = "wdr";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x95a8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_breakAVR_expect_assembler_correctly(void)
{
  char *line = "break";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x9598,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sev_expect_assembler_correctly(void)
{
  char *line = "sev";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x9438,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_clv_expect_assembler_correctly(void)
{
  char *line = "clv";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  Try{
  TEST_ASSERT_EQUAL_HEX16(0x94b8,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_INC_given_R7_expect_assembler_correctly(void)
{
  char *line = "R7";
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
  byte_number = ser(tokenizer ,codeMemoryPtr);
  TEST_FAIL_MESSAGE("Expected ERR_BEYOND_LIMIT exception to be thrown, but none received.");
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_add_given_R16_R26_expect_assemble_correctly(void)
{
  char *line = "R16, R26";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = addRdRr(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x0a0f ,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2,byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_adc_given_R6_R16_expect_assemble_correctly(void)
{
  char *line = "R6, R16";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = adc(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x601e ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sub_given_R2_r12_expect_assemble_correctly(void)
{
  char *line = "R2, r12";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = sub(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x2c18 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_sbc_given_r0_R1_expect_assemble_correctly(void)
{
  char *line = "r0,r1";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = sbc(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x0108 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_and_given_R3_R23_expect_assemble_correctly(void)
{
  char *line = "R3,R23";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = andRdRr(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x3722 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_or_given_R10_R9_expect_assemble_correctly(void)
{
  char *line = "R10,R9";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = orRdRr(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xa928 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_eor_given_R16_R26_expect_assemble_correctly(void)
{
  char *line = "R24,R26";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = eor(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x8a27 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_mul_given_R30_R31_expect_assemble_correctly(void)
{
  char *line = "R30,R31";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = mul(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xef9f ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_mov_given_R1_R2_expect_assemble_correctly(void)
{
  char *line = "R1,R2";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = mov(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x122c ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cpse_given_R6_R8_expect_assemble_correctly(void)
{
  char *line = "R6,R8";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = cpse(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x6810 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cp_given_R18_R19_expect_assemble_correctly(void)
{
  char *line = "R18,R19";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = cp(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x2317 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_cpc_given_R3_R4_expect_assemble_correctly(void)
{
  char *line = "R3,R4";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = cpc(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x3404 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_muls_given_R18_R19_expect_assemble_correctly(void)
{
  char *line = "R18,R19";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = muls(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x2302 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_mulsu_given_R20_R23_expect_assemble_correctly(void)
{
  char *line = "R20,R23";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = mulsu(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x4703 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_mulsu_given_R25_R23_expect_exception_beyond_limit(void)
{
  char *line = "R25,R23";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = mulsu(tokenizer ,codeMemoryPtr);
  //TEST_ASSERT_EQUAL_HEX16(0x4703 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_fmul_given_R17_R18_expect_exception_beyond_limit(void)
{
  char *line = "R17,R18";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = fmul(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x1a03 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_fmuls_given_R18_R19_expect_exception_beyond_limit(void)
{
  char *line = "R18,R19";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = fmuls(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xa303 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_fmulsu_given_R20_R21_expect_exception_beyond_limit(void)
{
  char *line = "R20,R21";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  tokenizer = createTokenizer(line);
  Try{
  byte_number = fmulsu(tokenizer ,codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xcd03 ,*(uint16_t *)codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_INC_R7_expect_assemble_correctly(void)
{
  char *line = "inc R7";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
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
  uint8_t codeMemoryPtr[2];
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
  uint8_t codeMemoryPtr[2];
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

void test_assembleOneInstruction_given_Rl_r31_expect_assemble_correctly(void)
{
  char *line = "roL r31";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0xff1f,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2 , byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_mov_R6_r16_expect_assemble_correctly(void)
{
  char *line = "mov r6,r16";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
  TEST_ASSERT_EQUAL_HEX16(0x602e,*(uint16_t *)codeMemoryPtr);
  TEST_ASSERT_EQUAL(2 , byte_number);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_trash_r31_expect_exception_not_found_thrown(void)
{
  char *line = "trash r31";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembleOneInstruction_given_rubish_expect_exception_thrown(void)
{
  char *line = "*&$^&$";
  Token *token;
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[1];
  int byte_number = 0;

  Try{
  tokenizer = createTokenizer(line);
  byte_number = assembleOneInstruction(tokenizer , codeMemoryPtr);
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

void test_assembler_breq_given_pc_5_expect_assemble_correctly(void)
{
  char *line = "pc+5";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = breq(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf021 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_breq_given_pc_5_expect_assemble_correctly(void)
{
  char *line = "breq pc+5";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf021 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brne_given_pc_8_expect_assemble_correctly(void)
{
  char *line = "brne pc+8";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf439 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brcs_given_pc_1_expect_assemble_correctly(void)
{
  char *line = "brcs pc+1";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf000 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brcc_given_pc_9_expect_assemble_correctly(void)
{
  char *line = "brcc pc+9";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf440 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brsh_given_pc_4_expect_assemble_correctly(void)
{
  char *line = "brsh pc+4";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf418 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brlo_given_pc_negative_2_expect_assemble_correctly(void)
{
  char *line = "brlo pc-2";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf3e8 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brmi_given_pc_negative_5_expect_assemble_correctly(void)
{
  char *line = "brmi pc-5";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf3d2 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brpl_given_pc_20_expect_assemble_correctly(void)
{
  char *line = "brpl pc+20";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf49a ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brlt_given_pc_10_expect_assemble_correctly(void)
{
  char *line = "brge pc+10";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf44c ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brlt_given_pc_16_expect_assemble_correctly(void)
{
  char *line = "brlt pc+16";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf07c ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brhs_given_pc_negative_10_expect_assemble_correctly(void)
{
  char *line = "brhs pc-10";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf3ad ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brhc_given_pc_negative_1_expect_assemble_correctly(void)
{
  char *line = "brhc pc-1";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf7f5 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brts_given_pc_44_expect_assemble_correctly(void)
{
  char *line = "brts pc+44";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf15e ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brtc_given_pc_50_expect_assemble_correctly(void)
{
  char *line = "brtc pc+50";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf58e ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brvs_given_pc_negative_14_expect_assemble_correctly(void)
{
  char *line = "brvs pc-14";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf38b ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brvc_given_pc_negative_4_expect_assemble_correctly(void)
{
  char *line = "brvc pc-4";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf7db ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brie_given_pc_7_expect_assemble_correctly(void)
{
  char *line = "brie pc+7";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf037 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_brid_given_pc_negative_7_expect_assemble_correctly(void)
{
  char *line = "brid pc-7";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf7c7 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_rjmp_pc_550_expect_assemble_correctly(void)
{
  char *line = "rjmp pc+550";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xc225 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_rjmp_pc_negative_3550_expect_exception(void)
{
  char *line = "rjmp pc-3550";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_rcall_pc_1550_expect_assemble_correctly(void)
{
  char *line = "rcall pc+1550";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xd60d ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_andi_expect_assemble_correctly(void)
{
  char *line = "andi r30,23";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x71e7 ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_ori_expect_assemble_correctly(void)
{
  char *line = "ori r29,45";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x62dd ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_subi_expect_assemble_correctly(void)
{
  char *line = "subi r16,25";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x5109 ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_sbci_expect_assemble_correctly(void)
{
  char *line = "andi r19,30";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x713e ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_ldi_expect_assemble_correctly(void)
{
  char *line = "ldi r24,44";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xe28c ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_cbr_expect_assemble_correctly(void)
{
  char *line = "cbr r20,55";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x7c48 ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_sbr_expect_assemble_correctly(void)
{
  char *line = "sbr r31,10";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x60fa ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_cpi_expect_assemble_correctly(void)
{
  char *line = "cpi r26,63";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[2];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x33af ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_adiw_expect_assemble_correctly(void)
{
  char *line = "adiw r24,40";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[3];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9688 ,*(uint16_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_adiw_given_odd_register_expect_invalid_register(void)
{
  char *line = "adiw r25,40";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[3];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_call_expect_assemble_correctly(void)
{
  char *line = "call 3999999";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX32(0x95ef08ff ,*(uint32_t *)codeMemoryPtr); //d60d
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_call_expect_beyond_limit(void)
{
  char *line = "call 5999999";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_jmp_expect_assemble_correctly(void)
{
  char *line = "jmp 0";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX32(0x940c0000 ,*(uint32_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_bset_expect_assemble_correctly(void)
{
  char *line = "bset 4";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9448 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_bclr_expect_assemble_correctly(void)
{
  char *line = "bclr 7";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x94f8 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_sbi_expect_assemble_correctly(void)
{
  char *line = "sbi 10,4";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x9a54 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_cbi_expect_assemble_correctly(void)
{
  char *line = "cbi 20,7";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0x98a7 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_bst_expect_assemble_correctly(void)
{
  char *line = "bst R9,1";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xfa91 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_assembleOneStruction_bld_expect_assemble_correctly(void)
{
  char *line = "bld R15,6";
  Tokenizer *tokenizer;
  uint8_t codeMemoryPtr[4];
  int byte_number = 0;

  Try{
    tokenizer = createTokenizer(line);
    byte_number = assembleOneInstruction(tokenizer ,codeMemoryPtr);
    TEST_ASSERT_EQUAL_HEX16(0xf8f6 ,*(uint16_t *)codeMemoryPtr);
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
  }
}

void test_getToken_given_random_line(void){
  char *line = "inc R12 pc- +++";
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
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("pc",token->str);
  //pushBackToken(tokenizer ,token);
  freeToken(token);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("-",token->str);
  freeToken(token);

  token = getToken(tokenizer);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE,token->type);
  TEST_ASSERT_EQUAL_STRING("+",token->str);
  freeToken(token);
}

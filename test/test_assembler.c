#include "unity.h"
#include "assembler.h"
#include "getoperand.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_assembler_INC_given_R16_expect_opcode(void)
{
  char *instruction = "R16";

  TEST_ASSERT_EQUAL(16,adc(instruction));
}

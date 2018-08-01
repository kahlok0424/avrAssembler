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

void test_assembler_INC_given_R16_expect_opcode(void)
{
  char *line = "inc R16";
  test_binary();
  Try{
  TEST_ASSERT_EQUAL(16,inc(line));
}Catch(ex){
  dumpTokenErrorMessage(ex, 1);
}
}

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#define OPERAND_TYPE_RD 1
#define TokenMatches(token,str2cmp)  (strcmp(token,str2cmp )== 0)

typedef struct {
  char *str;
  int operandType;
  int opCode;
}instruc;

static const instruc instrucs[] = {
  {"INC" , OPERAND_TYPE_RD , 0b1001010},
  {"DEC" , OPERAND_TYPE_RD , 0b1001010}
};

int inc(char *line);
void test_binary(void);

#endif // _ASSEMBLER_H

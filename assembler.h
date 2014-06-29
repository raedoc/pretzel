#ifndef _PRETZEL_ASSEMBLER_H_
#define _PRETZEL_ASSEMBLER_H_

typedef struct{
  char *name;
  long line;
  char **arguments;
}Instruction;

Instruction **assemble_source(char *path);
Instruction *extract_instruction(char *line, long lineNumber);

#endif

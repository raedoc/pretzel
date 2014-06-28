#ifndef _PRETZEL_ASSEMBLER_H_
#define _PRETZEL_ASSEMBLER_H_

typedef struct{
  char *name;
  long line;
  char **arguments;
}instruction;

instruction **assemble_source(char *path);
instruction *extract_instruction(char *line, long lineNumber);

#endif

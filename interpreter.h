#ifndef _PRETZEL_INTERPRETER_H_
#define _PRETZEL_INTERPRETER_H_

#include "assembler.h"

typedef struct{
  long sp;
  long ip;
  char flags;
  char *ram;
} vm;

void interpret_instructions(instruction **instructions);

#endif

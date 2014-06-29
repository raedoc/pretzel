#ifndef _PRETZEL_INTERPRETER_H_
#define _PRETZEL_INTERPRETER_H_

#include "assembler.h"

typedef struct{
  long ip;
  char *ram;
} Vm;

Vm *create_vm_instance(void);
void load_instructions(Vm *instance, Instruction **instructions);
void run_vm_instance(Vm *instance);

#endif

#ifndef _PRETZEL_INTERPRETER_H_
#define _PRETZEL_INTERPRETER_H_

#include "assembler.h"

typedef struct{
  long ip;
  char *ram;
} vm;

vm *create_vm_instance(void);
void load_instructions(vm *instance, instruction **instructions);
void run_vm_instance(vm *instance);

#endif

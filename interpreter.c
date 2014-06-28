#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"

typedef struct {
  const char* name;
  void (*func)(void);
}instruction_bytecode_handler;

void handle_noop(void) {
  fprintf(stderr, "ok, noop then\n");
}

const instruction_bytecode_handler INSTRUCTION_BYTECODE_LIST[] = {
  { "noop", handle_noop },
  { 0 }
};

vm *create_vm_instance(void) {
  vm *instance = NULL;
  instance = (vm*)malloc(sizeof(instance));
  instance->ip = 0;
  instance->ram = (char*)malloc(sizeof(char) * 16 * 1024);
  bzero(instance->ram, 16 * 1024);
  return instance;
}

int instruction_bytecode_index(instruction *needle) {
  long index;
  instruction_bytecode_handler current;

  for (index = 0; INSTRUCTION_BYTECODE_LIST[index].name != 0; index++) {
    if(strcmp(INSTRUCTION_BYTECODE_LIST[index].name, needle->name) == 0) {
      return index;
    }
  }

  return -1;
}

void load_instructions(vm *instance, instruction **instructions) {
  instruction *current;
  long currentInstruction, bytecodeIndex, currentPosition = 0;

  for (currentInstruction = 0; current = instructions[currentInstruction]; currentInstruction++) {
    if ((bytecodeIndex = instruction_bytecode_index(current)) > -1) {
      instance->ram[currentPosition++] = bytecodeIndex + 1;
    }
  }
}

void run_vm_instance(vm *instance) {
  char instruction;
  while ((instruction = instance->ram[instance->ip]) != 0) {
    INSTRUCTION_BYTECODE_LIST[instruction - 1].func();
    instance->ip++;
  }
}

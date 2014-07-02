#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"

typedef struct {
  const char* name;
  void (*generate)(Vm *);
  void (*interpret)(Vm *);
}BytecodeHandler;

void generate_noop(Vm *instance) {
  instance->ram[instance->ip++] = 0x1;
}

void generate_stop(Vm *instance) {
  instance->ram[instance->ip++] = 0x0;
}

void handle_noop(Vm *instance) {
  fprintf(stderr, "ok, noop then\n");
}

void handle_stop(Vm *instance) {
  fprintf(stderr, "stopping\n");
}

const BytecodeHandler INSTRUCTION_BYTECODE_LIST[] = {
  { "stop", generate_stop, handle_stop },
  { "noop", generate_noop, handle_noop },
  { 0 }
};

Vm *create_vm_instance(void) {
  Vm *instance = NULL;
  instance = (Vm *)malloc(sizeof(Vm));
  instance->ip = 0;
  instance->ram = (char*)malloc(sizeof(char) * 16 * 1024);
  bzero(instance->ram, 16 * 1024);
  return instance;
}

int instruction_bytecode_index(Instruction *needle) {
  long index;

  for (index = 0; INSTRUCTION_BYTECODE_LIST[index].name != 0; index++) {
    if(strcmp(INSTRUCTION_BYTECODE_LIST[index].name, needle->name) == 0) {
      return index;
    }
  }

  return -1;
}

void load_instruction_to_instance(Vm *instance, Instruction *instruction) {
  BytecodeHandler handler;
  long bytecodeIndex;

  if ((bytecodeIndex = instruction_bytecode_index(instruction)) > -1) {
    INSTRUCTION_BYTECODE_LIST[bytecodeIndex].generate(instance);
  }
}

void load_instructions(Vm *instance, Instruction **instructions) {
  Instruction *current;
  long currentInstruction;

  instance->ip = 0;
  for (currentInstruction = 0; current = instructions[currentInstruction]; currentInstruction++) {
    load_instruction_to_instance(instance, current);
  }
}

void run_vm_instance(Vm *instance) {
  char instruction;

  instance->ip = -1;
  while ((instruction = instance->ram[++(instance->ip)]) != 0) {
    INSTRUCTION_BYTECODE_LIST[instruction].interpret(instance);
  }
}

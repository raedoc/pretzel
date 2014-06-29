#include "assembler.h"
#include "interpreter.h"
#include "cutest.h"

#define TEST_CHECK_STRING(s1, s2) do { TEST_CHECK(strcmp(s1, s2) == 0); } while(0)

void test_empty_assembler(void) {
  Instruction **bytecode = assemble_source("");
  TEST_CHECK(bytecode[0] == NULL);
}

void test_valid_assembler(void) {
  Instruction **bytecode = assemble_source("mov croco, dingus");
  TEST_CHECK(bytecode[0] != NULL);
}

void test_assembler_comment(void) {
  Instruction **bytecode = assemble_source(";add ham, rye");
  TEST_CHECK(bytecode[0] == NULL);
}

void test_extract_unary_assembler(void) {
  Instruction *extracted = extract_instruction("sigh", 777);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 777);
    TEST_CHECK_STRING(extracted->name, "sigh");
    TEST_CHECK(extracted->arguments[0] == NULL);
  }
}

void test_extract_assembler(void) {
  Instruction *extracted = extract_instruction("wat taco, brah", 666);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 666);
    TEST_CHECK_STRING(extracted->name, "wat");
    TEST_CHECK_STRING(extracted->arguments[0], "taco");
    TEST_CHECK_STRING(extracted->arguments[1], "brah");
    TEST_CHECK(extracted->arguments[2] == NULL);
  }
}

void test_extract_assembler_comments(void) {
  Instruction *extracted = extract_instruction("oh no ;OMG", 666);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 666);
    TEST_CHECK_STRING(extracted->name, "oh");
    TEST_CHECK_STRING(extracted->arguments[0], "no");
    TEST_CHECK(extracted->arguments[1] == NULL);
  }
}

void test_create_vm_instance(void) {
  Vm *instance = create_vm_instance();
  TEST_CHECK(instance != NULL);
  TEST_CHECK(instance->ip == 0);
  TEST_CHECK(instance->ram != NULL);
}

void test_load_instructions(void) {
  Vm *instance = create_vm_instance();
  Instruction **instructions = assemble_source("noop");
  load_instructions(instance, instructions);
  TEST_CHECK(instance->ram[0] == 1);
  TEST_CHECK(instance->ram[1] == 0);
}

void test_run_vm(void) {
  Vm *instance = create_vm_instance();
  Instruction **instructions = assemble_source("noop\nnoop");
  load_instructions(instance, instructions);
  run_vm_instance(instance);
  TEST_CHECK(instance->ip == 2);
}

TEST_LIST = {
  { "assembling empty source", test_empty_assembler },
  { "assembling comments", test_assembler_comment },
  { "assembling valid source", test_valid_assembler },
  { "extracting a unary instruction", test_extract_unary_assembler },
  { "extracting a multiargument instruction", test_extract_assembler },
  { "extracting a multiargument instruction with comments afterwards", test_extract_assembler_comments },
  { "creating a vm", test_create_vm_instance },
  { "running a set of instructions", test_load_instructions },
  { "running vm", test_run_vm },
  { 0 }
};

#include "assembler.h"
#include "interpreter.h"
#include "cutest.h"

#define TEST_CHECK_STRING(s1, s2) do { TEST_CHECK(strcmp(s1, s2) == 0); } while(0)

void test_empty_assembler(void) {
  instruction **bytecode = assemble_source("");
  TEST_CHECK(bytecode[0] == NULL);
}

void test_valid_assembler(void) {
  instruction **bytecode = assemble_source("mov croco, dingus");
  TEST_CHECK(bytecode[0] != NULL);
}

void test_assembler_comment(void) {
  instruction **bytecode = assemble_source(";add ham, rye");
  TEST_CHECK(bytecode[0] == NULL);
}

void test_extract_unary_assembler(void) {
  instruction *extracted = extract_instruction("sigh", 777);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 777);
    TEST_CHECK_STRING(extracted->name, "sigh");
    TEST_CHECK(extracted->arguments[0] == NULL);
  }
}

void test_extract_assembler(void) {
  instruction *extracted = extract_instruction("wat taco, brah", 666);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 666);
    TEST_CHECK_STRING(extracted->name, "wat");
    TEST_CHECK_STRING(extracted->arguments[0], "taco");
    TEST_CHECK_STRING(extracted->arguments[1], "brah");
    TEST_CHECK(extracted->arguments[2] == NULL);
  }
}

void test_extract_assembler_comments(void) {
  instruction *extracted = extract_instruction("oh no ;OMG", 666);
  if (TEST_CHECK(extracted != NULL)) {
    TEST_CHECK(extracted->line == 666);
    TEST_CHECK_STRING(extracted->name, "oh");
    TEST_CHECK_STRING(extracted->arguments[0], "no");
    TEST_CHECK(extracted->arguments[1] == NULL);
  }
}

TEST_LIST = {
  { "assembling empty source", test_empty_assembler },
  { "assembling comments", test_assembler_comment },
  { "assembling valid source", test_valid_assembler },
  { "extracting a unary instruction", test_extract_unary_assembler },
  { "extracting a multiargument instruction", test_extract_assembler },
  { "extracting a multiargument instruction with comments afterwards", test_extract_assembler_comments },
  { 0 }
};

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "assembler.h"

int can_assemble(char *string) {
  int i, length;
  char c;
  for (i = 0, length = strlen(string), c = string[c]; c; i++) {
    switch(c) {
      case ' ':
      case '\t':
        continue;
      case ';':
        return 0;
      default:
        return 1;
    }
  }
  return 0;
}

Instruction *extract_instruction(char *line, long lineNumber) {
  Instruction *extracted = NULL;
  char *running = strdup(line);
  char *word = NULL;
  long argumentCount = 0;
  const char delimiters[] = " ,\t";

  extracted = (Instruction *)malloc(sizeof(Instruction));
  extracted->line = lineNumber;
  extracted->arguments = malloc(sizeof(char*));
  extracted->arguments[0] = NULL;

  while (word = strsep(&running, delimiters)) {
    if (can_assemble(word)) {
      if (extracted->name == NULL) {
        extracted->name = strdup(word);
      } else {
        extracted->arguments = realloc(extracted->arguments, (argumentCount + 2) * sizeof(char*));
        extracted->arguments[argumentCount++] = strdup(word);
        extracted->arguments[argumentCount] = NULL;
      }
    }
  }

  return extracted;
}

Instruction **assemble_source(char *source) {
  Instruction **assembled = NULL;
  Instruction *extracted = NULL;
  char *line = NULL;
  long lineNumber = 0;
  long extractionCount = 0;
  char *sourceCopy = strdup(source);

  assembled = malloc(sizeof(Instruction *));
  assembled[0] = NULL;

  while (line = strsep(&sourceCopy, "\n")) {
    line = strsep(&line, ";");
    if (can_assemble(line)) {
      assembled = realloc(assembled, (extractionCount + 2) * sizeof(Instruction*));
      assembled[extractionCount++] = extract_instruction(line, lineNumber++);
      assembled[extractionCount] = NULL;
    }
  }

  return assembled;
}

#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "interpreter.h"

long calculate_size(FILE *file) {
  long size;

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

char *read_sized_content(FILE *file, long size) {
  char *content;

  content = (char *)malloc(size + 1);
  fread(content, size, 1, file);

  return content;
}

char *read_source(char *path) {
  FILE *file;
  char *source;

  if ((file = fopen(path, "rb")) == NULL) {
    fprintf(stderr, "Unable to read file at %s\n", path);
    return NULL;
  }

  source = read_sized_content(file, calculate_size(file));
  fclose(file);

  return source;
}

int main(int argc, char **argv) {
  instruction *assembled;
  char *source;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <source-file>", argv[0]);
    return 1;
  }

  source = read_source(argv[1]);
  if (source == NULL) {
    return 1;
  }

  assembled = assemble_source(source);
  interpret_instructions(assembled);
  free(assembled);
  free(source);

  return 0;
}

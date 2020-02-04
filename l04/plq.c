#include <stdlib.h>
#include <stdio.h>

// This program has a serious bug that results in undefined behavior
// through an invalid memory access. Try fixing it!
//
// To make the problem more visible, compile with the address sanitizer
// enabled: pass "-fsanitize=address" to your compiler.

char* makeChar() {
  char* c = (char*)malloc(1);
  return c;
}

int main() {
  char* c = makeChar();
  *c = 'A';
  *(c + 1) = 'B';
  printf("%c %c\n", *c, *(c + 1));
  free(c);
  return 0;
}

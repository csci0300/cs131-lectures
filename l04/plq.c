#include <stdlib.h>
#include <stdio.h>

char* makeChar() {
  char* c = (char*)malloc(1);
  return c;
}

int main() {
  char* c = makeChar();
  *c = 'A';
  *(c + 1) = 'B';
  printf("%c %c\n", *c, *(c + 1));
  return 0;
}

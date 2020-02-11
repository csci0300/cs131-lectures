#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>
#include "hexdump.h"

struct ints_and_chars {
  int i1;
  char c1;
  int i2;
  char c2;
  int i3;
  char c3;
};

void f() {
  struct ints_and_chars x = {.i1 = 1, .c1 = 'A', .i2 = 2, .c2 = 'B', .i3 = 3, .c3 = 'C'};

  printf("sizeof(struct ints_and_chars): %lu\n", sizeof(struct ints_and_chars));
  printf("alignof(struct ints_and_chars): %lu\n", alignof(struct ints_and_chars));

  printf("\nmembers:\n");
  hexdump(&x.i1, sizeof(x.i1));
  hexdump(&x.c1, sizeof(x.c1));
  hexdump(&x.i2, sizeof(x.i2));
  hexdump(&x.c2, sizeof(x.c2));
  hexdump(&x.i3, sizeof(x.i3));
  hexdump(&x.c3, sizeof(x.c3));
}

int main() {
  f();
}

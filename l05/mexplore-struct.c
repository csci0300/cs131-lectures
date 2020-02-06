#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "hexdump.h"

typedef struct x {
  int i1;
  int i2;
  int i3;
  char c1;
  char c2;
  char c3;
} x_t;

void f() {
  x_t* x = (x_t*)malloc(sizeof(x_t));
  x->i1 = 1;
  x->i2 = 2;
  x->c3 = 'X';
  printf("i2: %d\n", x->i2);

  printf("whole struct:\n");
  hexdump(x, sizeof(x_t));


  printf("\nmembers:\n");
  hexdump(&x->i1, sizeof(x->i1));
  hexdump(&x->i2, sizeof(x->i2));
  hexdump(&x->i3, sizeof(x->i3));
  hexdump(&x->c1, sizeof(x->c1));
  hexdump(&x->c2, sizeof(x->c2));
  hexdump(&x->c3, sizeof(x->c3));
}

int main() {
  f();
}

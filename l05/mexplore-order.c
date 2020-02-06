#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include "hexdump.h"

void f() {
  int i1 = 1;
  int i2 = 2;
  int i3 = 3;
  char c1 = 'A';
  char c2 = 'B';
  char c3 = 'C';

  hexdump(&i1, sizeof(i1));
  hexdump(&i2, sizeof(i2));
  hexdump(&i3, sizeof(i3));
  hexdump(&c1, sizeof(c1));
  hexdump(&c2, sizeof(c2));
  hexdump(&c3, sizeof(c3));
}

int main() {
    f();
}

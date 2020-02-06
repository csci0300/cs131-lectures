#include <stdio.h>
#include "hexdump.h"

void f() {
  int i1 = 1;
  int i2 = -1;

  hexdump(&i1, sizeof(i1));
  hexdump(&i2, sizeof(i2));

  int i3 = i1 + i2;
  hexdump(&i3, sizeof(i3));
}

int main() {
    f();
}

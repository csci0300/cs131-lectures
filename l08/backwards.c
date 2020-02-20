#include <stdio.h>

unsigned a = 12;
int b = 15;

extern int sum(void);

int main() {
  printf("a: %u\n", a);
  printf("b: %d\n", b);
  printf("sum: %d\n", sum());
}

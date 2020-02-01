#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* f() {
  int* i_ptr = (int*)malloc(8);
  *i_ptr = 42;
  *(i_ptr + 1) = 123;

  return i_ptr;
}

void g() {
  int b = 666;
  printf("%d\n", b);
}

int main() {
  int* mains_i_ptr = f();
  g();
  printf("%p\n", &mains_i_ptr);
  printf("%p\n", mains_i_ptr);
  printf("%d\n", *mains_i_ptr);
  printf("%d\n", *(mains_i_ptr + 1));

  free(mains_i_ptr);
}

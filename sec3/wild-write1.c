#include <stdlib.h>
#include <stdio.h>

int main() {
  // make a 4-byte allocation for an int, set the value to 42
  int* i_ptr = (int*)malloc(sizeof(int));
  i_ptr[0] = 42;

  // print the address of the allocation
  printf("i_ptr: %p\n", i_ptr);

  // now write to 4 bytes of memory starting 4
  // bytes beyond the end of the valid allocation
  // (i_ptr + 8 bytes).
  // This is a WILD WRITE, as we're writing to heap memory
  // that we never allocated.
  //
  // the following three lines all mean the same thing!
  // any one of them will cause an error if you compile with
  // -fsanitize=address, but may seem to work fine if you
  // compile without that flag.
  i_ptr[2] = 123;
  *(i_ptr + 2) = 123;
  *((char*)i_ptr + sizeof(int) * 2) = 123;

  printf("*i_ptr: %d\n", *i_ptr);

  // if you leave out this line and compile with -fsanitize=address,
  // you will get a complaint about a memory leak
  free(i_ptr);
}

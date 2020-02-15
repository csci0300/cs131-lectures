#include <stdlib.h>
#include <stdio.h>

int main() {
  // make a 4-byte allocation for an int, set the value to 42
  int* i_ptr = (int*)malloc(sizeof(int));
  i_ptr[0] = 42;

  // make a 4-byte allocation for another int, set to 999
  int* i_ptr2 = (int*)malloc(sizeof(int));
  i_ptr2[0] = 999;

  // print the addresses of the allocations.
  // On x86-64 Linux (Ubuntu 18.04), the second address is
  // likely 0x20 beyond the first address (hex 20 = decimal 32).
  printf("i_ptr: %p\n", i_ptr);
  printf("i_ptr2: %p\n", i_ptr2);

  // now write to 4 bytes of memory starting 28
  // bytes beyond the end of the valid allocation
  // (i_ptr + 32 bytes).
  //
  // the following three lines all mean the same thing!
  //
  // Again, this is a WILD WRITE. But this time, the address
  // sanitizer sadly will not help us find it, because the
  // memory we write to is part of a valid allocation. It's
  // still undefined behavior to do this, and your program might
  // do anything -- but the address sanitizer cannot detect this.
  //
  // This illustrates that passing the address sanitizer does
  // not guarantee that your program is free of memory bugs.
  // Passing the sanitizer is a necessary condition for memory
  // safety, but not a sufficient one.
  i_ptr[8] = 123;
  *(i_ptr + 8) = 123;
  *((char*)i_ptr + sizeof(int) * 8) = 123;

  printf("*i_ptr: %d\n", *i_ptr);
  // will likely print "*i_ptr2: 123", even though we set the
  // value at i_ptr2 to 999 above.
  printf("*i_ptr2: %d\n", *i_ptr2);

  // if you leave out this line and compile with -fsanitize=address,
  // you will get a complaint about a memory leak
  free(i_ptr);
  free(i_ptr2);
}

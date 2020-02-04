#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

char* global_st = "Hello CS131!";

void f() {
    hexdump(global_st, 13);  // 12 characters plus NUL terminator

    char* alloc_st = malloc(14);
    sprintf(alloc_st, "We <3 systems");
    hexdump(alloc_st, 14);  // 13 characters plus NUL terminator

    // This used to segfault when trying to modify a literal string,
    // but with a string in dynamic lifetime memory, it works fine.
    for (int i = 0; i < 13; i++) {
      if (*(alloc_st + i) == '<') {
        *(alloc_st) = 'E';
        *(alloc_st + i) = '>';
      }
    }

    hexdump(alloc_st, 14);
}

int main() {
    f();
}

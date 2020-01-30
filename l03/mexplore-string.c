#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

//                | static, const global string; in static segment
//                | of memory (= static lifetime).
//                | (can't be modified, because it's in the read-only
//                | section of the static memory segment)
//                v
char* global_st = "Hello CS131!";

void f() {
    hexdump(global_st, 13);  // 12 characters plus NUL terminator

    //               | static, const string (read-only).
    //               | Literal strings are in the read-only section of
    //               | the static lifetime memory segment.
    //               | The *address* local_st is a local variable, but
    //               | right hand side is an address in the read-only
    //               | section, so local_st will *point* to the read-only
    //               | segment.
    //               v
    char* local_st = "We <3 systems";
    hexdump(local_st, 14);  // 13 characters plus NUL terminator

    // This segfaults (as it did in the lecture) because it tries to
    // modify a ready-only literal string.
    //for (int i = 0; i < 13; i++) {
    //  if (*(local_st + i) == '<') {
    //    *(local_st + i) = 'E';
    //    *(local_st + i) = '>';
    //  }
    //}

    char* allocated_st = (char*)malloc(100);
    sprintf(allocated_st, "We <3 systems");

    // this works!
    for (int i = 0; i < 13; i++) {
      if (*(allocated_st + i) == '<') {
        *(allocated_st + i) = 'E';
        *(allocated_st + i + 1) = '>';
      }
    }

    hexdump(allocated_st, 14);  // 13 characters plus NUL terminator
}

int main() {
    f();
}

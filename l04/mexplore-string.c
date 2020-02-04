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

    //               | The *address* local_st is a local variable, but
    //               | right hand side is an address in the read-only
    //               | section, so local_st will *point* to the read-only
    //               | segment.
    //               v
    char* local_st = "We <3 systems";
    hexdump(local_st, 14);  // 13 characters plus NUL terminator

    // This segfaults because it tries to
    // modify a ready-only literal string.
    for (int i = 0; i < 13; i++) {
      if (*(local_st + i) == '<') {
        *(local_st + i) = 'E';
        *(local_st + i) = '>';
      }
    }

    hexdump(local_st, 14);
}

int main() {
    f();
}

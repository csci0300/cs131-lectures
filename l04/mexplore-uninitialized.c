#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

void f() {
    char* allocated_st1 = (char*)malloc(100);
    char* allocated_st2 = (char*)malloc(100);
    sprintf(allocated_st1, "C programming is cool");
    sprintf(allocated_st2, "Strings are sequences of bytes");

    hexdump(allocated_st1, 100);
    hexdump(allocated_st2, 100);

    free(allocated_st1);
    free(allocated_st2);

    char* allocated_again_st = (char*)malloc(100);
    // what will this print? whatever is in the uninitialized memory!
    hexdump(allocated_again_st, 100);
}

int main() {
    f();
}

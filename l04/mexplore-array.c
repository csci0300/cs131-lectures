#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

void f() {
    int arr[] = { 1, 2, 3, 4 };

    hexdump(arr, 16);

    //printf("--------\n");

    //int arr2[5];

    //arr2[0] = 1;
    //arr2[1] = 2;
    //arr2[2] = 128;
    //arr2[3] = 17;
    //arr2[4] = 0;

    //hexdump(arr2, 20);
}

int main() {
    f();
}

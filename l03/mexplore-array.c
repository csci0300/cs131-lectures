#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

void f() {
    int arr2[] = { 1, 2, 3, 4 };

    hexdump(arr2, 16);

    printf("--------\n");

    int arr[5];

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 128;
    arr[3] = 17;
    arr[4] = 0;

    hexdump(arr, 20);

    for (unsigned int i = 0; i < sizeof(arr) / sizeof(int); i++) {
      arr[i] -= 1;
    }

    hexdump(arr, sizeof(arr));
}

int main() {
    f();
}

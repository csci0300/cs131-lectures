#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int check_signed_increment(int x) {
    assert(x + 1 > x);
    return x + 1;
}

int main(int argc, char** argv) {
    assert(argc >= 2);
    int x = strtol(argv[1], NULL, 0);

    int x_incr = check_signed_increment(x);
    printf("%d + 1 = %d\n", x, x_incr);
}

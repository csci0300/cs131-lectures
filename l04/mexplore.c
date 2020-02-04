#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

char global_ch = 'A';
const char const_global_ch = 'B';

void g() {
    char local_ch_in_g = 'X';
    hexdump(&local_ch_in_g, 1);
}

void f() {
    char local_ch = 'C';
    char local_ch2 = 'D';
    char local_ch3 = 'E';

    hexdump(&global_ch, 1);
    hexdump(&const_global_ch, 1);
    hexdump(&local_ch, 1);
    hexdump(&local_ch2, 1);
    hexdump(&local_ch3, 1);

    g();
}

int main() {
    f();
}

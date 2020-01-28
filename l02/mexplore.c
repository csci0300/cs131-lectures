#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

char global_ch = 'A';
const char const_global_ch = 'B';

void f() {
    char local_ch = 'C';

    hexdump(&global_ch, 1);
    hexdump(&const_global_ch, 1);
    hexdump(&local_ch, 1);
}

int main() {
    f();
}

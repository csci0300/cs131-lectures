#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hexdump.h"

char global_ch = 'A';
const char const_global_ch = 'B';

char* f() {
    char local_ch = 'C';

    hexdump(&global_ch, 1);
    hexdump(&const_global_ch, 1);
    hexdump(&local_ch, 1);

    char* allocated_ch = (char*)malloc(1);
    *allocated_ch = 'D';

    return allocated_ch;
}

int main() {
    char* c = f();

    hexdump(c, 1);
}

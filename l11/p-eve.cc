#include "u-lib.hh"

void process_main() {
    unsigned i = 0;
    while (true) {
        ++i;
        if (i % 1024 == 0) {
            console_printf(0x0E00, "Hi, I'm Eve! #%d\n", i / 512);
        }

        sys_yield();
    }
}

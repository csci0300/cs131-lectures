#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sstream>

unsigned finish_checksum(const char*, unsigned) __attribute__((noinline));


unsigned checksum(const char* arg) {
    // initialize buffer
    union {
        char c[100];
        unsigned u[25];
    } buf;
    memset(&buf, 0, sizeof(buf));

    // copy string into an aligned local buffer
    for (size_t i = 0; arg[i] != 0; ++i) {
        buf.c[i] = arg[i];
    }

    // add 4-byte contiguous words
    unsigned u = 0;
    for (size_t i = 0; i < sizeof(buf) / sizeof(unsigned); ++i) {
        u += buf.u[i];
    }
    return finish_checksum(buf.c, u);
}


unsigned finish_checksum(const char*, unsigned u) {
    return u;
}


// run_shell(command)
//   Run `command` and print the first <=4096 bytes of its output.

void run_shell(const char* command) {
    FILE* f = popen(command, "r");
    char localbuf[4096];
    size_t n = fread(localbuf, 1, sizeof(localbuf) - 1, f);
    pclose(f);
    localbuf[n] = 0;
    fputs(localbuf, stdout);
}


int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        // skip evil strings
        if (strlen(argv[i]) > 4000
            || strchr(argv[i], '\'') != nullptr) {
            continue;
        }

        // Print our checksum
        printf("%s: checksum %08x, sha1 ", argv[i], checksum(argv[i]));

        // Print real checksum
        char commandbuf[4096];
        sprintf(commandbuf, "echo '%s' | sha1sum", argv[i]);
        run_shell(commandbuf);
    }
}

#include "iobench.hh"

int main() {
    FILE* f = stdout;
    if (isatty(fileno(f))) {
        f = fopen(DATAFILE, "w");
    }
    if (!f) {
        perror("fopen");
        exit(1);
    }

    size_t size = 51200000;
    size_t block_size = 512;
    char* buf = (char*) malloc(block_size);
    memset(buf, '6', block_size);
    double start = tstamp();

    size_t n = 0;
    while (n < size) {
        size_t r = fwrite(buf, 1, block_size, f);
        if (r != block_size) {
            perror("write");
            exit(1);
        }
        n += r;
        if (n % PRINT_FREQUENCY == 0) {
            report(n, tstamp() - start);
        }
    }

    fclose(f);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}

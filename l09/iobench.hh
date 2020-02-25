#ifndef IOBENCH_H
#define IOBENCH_H

#define _GNU_SOURCE 1
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <time.h>

static inline double tstamp(void) {
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
    return tv.tv_sec + tv.tv_nsec * 1.0e-9;
}

// Print a report to stderr of # bytes printed, elapsed time, and rate.
static inline void report(size_t n, double elapsed) {
    fprintf(stderr, "\r%zd bytes   %.3f sec   %g byte/sec     ",
            n, elapsed, n / elapsed);
}

// Return the size of a file.
static inline ssize_t filesize(int fd) {
    struct stat s;
    int r = fstat(fd, &s);
    if (r >= 0 && S_ISREG(s.st_mode) && s.st_size <= SSIZE_MAX) {
        return s.st_size;
    } else {
        return -1;
    }
}

#ifndef PRINT_FREQUENCY
#define PRINT_FREQUENCY 4096
#endif

#ifndef DATAFILE
#define DATAFILE "data"
#endif

#endif

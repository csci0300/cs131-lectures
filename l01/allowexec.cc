#include "allowexec.hh"
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cinttypes>
#include <cstring>
#include <sys/mman.h>
#include <sys/resource.h>

void check_system_call(int r, const char* syscall) {
    if (r == -1) {
        fprintf(stderr, "%s: %s\n", syscall, strerror(errno));
        exit(1);
    }
}

void limit_stack_size(size_t size) {
    struct rlimit rlim;
    int r = getrlimit(RLIMIT_STACK, &rlim);
    check_system_call(r, "getrlimit");
    if (rlim.rlim_cur > size) {
        rlim.rlim_cur = size;
        r = setrlimit(RLIMIT_STACK, &rlim);
        check_system_call(r, "setrlimit");
    }
}

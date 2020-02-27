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

#define PAGE_SIZE 4096
void allow_execute(const void* ptr, size_t size) {
    uintptr_t address = (uintptr_t) ptr;
    uintptr_t end_address = address + size;
    address = address & ~(uintptr_t) (PAGE_SIZE - 1);
    end_address = (end_address | (PAGE_SIZE - 1)) + 1;
    int r = mprotect((void*) address, end_address - address,
                     PROT_READ | PROT_WRITE | PROT_EXEC);
    check_system_call(r, "mprotect");
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

// Test if `s` is a number (a string completely parseable by `strtol`).
int strisnumber(const char* s) {
    char* ends;
    (void) strtol(s, &ends, 0);
    return s != ends && *ends == 0;
}

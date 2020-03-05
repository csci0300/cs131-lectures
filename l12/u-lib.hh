#ifndef WEENSYOS_U_LIB_HH
#define WEENSYOS_U_LIB_HH
#include "lib.hh"
#include "x86-64.h"
#if WEENSYOS_KERNEL
#error "u-lib.hh should not be used by kernel code."
#endif

// u-lib.hh
//
//    Support code for WeensyOS user-level processes.


// make_syscall
//    These functions define the WeensyOS system call calling convention.
//    We provide versions for system calls with 0-2 arguments.

inline uintptr_t make_syscall(int syscallno) {
    register uintptr_t rax asm("rax") = syscallno;
    asm volatile ("syscall"
            : "+a" (rax)
            : /* all input registers are also output registers */
            : "cc", "memory", "rcx", "rdx", "rsi", "rdi", "r8", "r9",
              "r10", "r11");
    return rax;
}

inline uintptr_t make_syscall(int syscallno, uintptr_t arg0) {
    register uintptr_t rax asm("rax") = syscallno;
    asm volatile ("syscall"
            : "+a" (rax), "+D" (arg0)
            :
            : "cc", "memory", "rcx", "rdx", "rsi", "r8", "r9", "r10", "r11");
    return rax;
}

inline uintptr_t make_syscall(int syscallno, uintptr_t arg0,
                              uintptr_t arg1) {
    register uintptr_t rax asm("rax") = syscallno;
    asm volatile ("syscall"
            : "+a" (rax), "+D" (arg0), "+S" (arg1)
            :
            : "cc", "memory", "rcx", "rdx", "r8", "r9", "r10", "r11");
    return rax;
}


// sys_getpid
//    Return current process ID.
inline pid_t sys_getpid() {
    return make_syscall(SYSCALL_GETPID);
}

// sys_yield
//    Yield control of the CPU to the kernel. The kernel will pick another
//    process to run, if possible.
inline void sys_yield() {
    make_syscall(SYSCALL_YIELD);
}

// sys_page_alloc(addr)
//    Allocate a page of memory at address `addr`. `Addr` must be page-aligned
//    (i.e., a multiple of PAGESIZE == 4096). Returns 0 on success and -1
//    on failure.
inline int sys_page_alloc(void* addr) {
    return make_syscall(SYSCALL_PAGE_ALLOC, (uintptr_t) addr);
}

// sys_getsysname()
//    Write the name of the current OS into `buf`.
inline int sys_getsysname(char* buf) {
    return make_syscall(SYSCALL_GETSYSNAME, (uintptr_t) buf);
}

// sys_panic(msg)
//    Panic.
[[noreturn]] inline void sys_panic(const char* msg) {
    make_syscall(SYSCALL_PANIC, (uintptr_t) msg);

    // should never get here
    while (true) {
    }
}

#endif

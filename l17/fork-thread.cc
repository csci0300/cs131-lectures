#include "helpers.hh"
#include <sched.h>
#include <sys/mman.h>

int child(void*);
void print();

int precious = 42;

int main() {
    // Allocate stack for child
    const int STACK_SIZE = 65536;
    char* stack =
      (char*)mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    if (stack == MAP_FAILED) {
        perror("mmap");
    }
    char* stack_top = stack + STACK_SIZE;

    // Start child thread, which calls child()
    long p1 = clone(&child, (void*)stack_top,
                    CLONE_VM | CLONE_FS | CLONE_FILES, NULL);
    assert(p1 >= 0);

    // Only parent executes here
    precious += 1;
    print();

    waitpid(p1, NULL, 0);
}

int child(void*) {
    // Child executes here
    precious *= 2;
    print();

    return 0;
}

void print() {
    // both parent and child run this
    char buf[100];
    snprintf(&buf[0], 100, "Hello from pid %d, precious=%d\n", getpid(),
             precious);
    if (write(1, buf, strlen(buf)) < 0) {
      perror("write");
    }
}

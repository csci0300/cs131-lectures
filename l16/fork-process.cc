#include "helpers.hh"

int precious = 42;

int main() {
    pid_t p1 = fork();
    assert(p1 >= 0);

    if (p1 == 0) {
      // child
      precious *= 2;
    } else {
      // parent
      precious += 1;
    }

    // both parent and child
    printf("Hello from pid %d (%s), precious=%d\n", getpid(),
           p1 ? "parent" : "child", precious);
}

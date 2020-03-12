#include "helpers.hh"

int main() {
    pid_t p1 = fork();
    assert(p1 >= 0);

    printf("Hello from pid %d\n", getpid());
}

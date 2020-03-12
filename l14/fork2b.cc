#include "helpers.hh"

int main() {
    pid_t initial_pid = getpid();
    printf("Hello from initial pid %d\n", initial_pid);

    pid_t p1 = fork();
    assert(p1 >= 0);

    pid_t p2 = fork();
    assert(p2 >= 0);

    if (getpid() != initial_pid) {
        printf("Hello from child pid %d\n", getpid());
    }
}

#include <unistd.h>
#include <thread>
#include <cstdio>
#include <cstring>

int child();
void print();

int precious = 42;

int main() {
    // Start child thread, which calls child()
    std::thread p1(child);

    // Only parent executes here
    precious += 1;
    print();

    p1.join();
}

int child() {
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

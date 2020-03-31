#include "helpers.hh"

int main() {
    const char* args[] = {
        "./myecho", // argv[0] is the string used to execute the program
        "Hello!",
        "Myecho should print these",
        "arguments.",
        nullptr
    };

    pid_t p = fork();

    if (p == 0) {
        fprintf(stderr, "About to exec myecho from pid %d\n", getpid());

        int r = execv("./myecho", (char**) args);

        fprintf(stderr, "Finished execing myecho from pid %d; status %d\n",
                getpid(), r);
    } else {
        fprintf(stderr, "Child pid %d should exec myecho\n", p);
    }
}

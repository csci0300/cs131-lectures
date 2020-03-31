#include "helpers.hh"

int main() {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r == 0);

    pid_t p1 = fork();
    assert(p1 >= 0);

    if (p1 == 0) {
        const char* message = "Hello, mama!\n";
        ssize_t nw = write(pipefd[1], message, strlen(message));
        assert(nw == (ssize_t) strlen(message));
        exit(0);
    }

    FILE* f = fdopen(pipefd[0], "r");
    while (!feof(f)) {
        char buf[BUFSIZ];
        if (fgets(buf, BUFSIZ, f) != nullptr) {
            printf("I got a message! It was “%s”\n", buf);
        }
    }
    printf("No more messages :(\n");
    fclose(f);
}

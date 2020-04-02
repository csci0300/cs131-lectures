#include "helpers.hh"

int main() {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r == 0);

    pid_t p1 = fork();
    assert(p1 >= 0);

    if (p1 == 0) {
        // child process
        const char* message = "Hello, mama!";
        printf("[child: %d] sending message\n", getpid());
        ssize_t nw = write(pipefd[1], message, strlen(message));
        assert(nw == (ssize_t) strlen(message));
        exit(0);
    }

    char buf[BUFSIZ];
    if (read(pipefd[0], buf, BUFSIZ) > 0) {
        printf("[parent: %d] I got a message! It was “%s”\n", getpid(), buf);
    }

    close(pipefd[0]);
    close(pipefd[1]);
}

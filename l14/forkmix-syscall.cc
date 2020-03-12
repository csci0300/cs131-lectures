#include "helpers.hh"

int main() {
    pid_t p1 = fork();
    assert(p1 >= 0);

    const char* text;
    if (p1 == 0) {
        text = "BABY\n";
    } else {
        text = "mama\n";
    }

    for (int i = 0; i != 1000000; ++i) {
        ssize_t s = write(STDOUT_FILENO, text, strlen(text));
        assert(s == (ssize_t) strlen(text));
    }
}

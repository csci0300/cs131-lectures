#include "helpers.hh"
#include <netdb.h>

void usage(int exit_status) {
    fprintf(stderr, "Usage: wdbclient [get KEY | set KEY VALUE | delete KEY]...\n");
    exit(exit_status);
}


int main(int argc, char** argv) {
    const char* host = "localhost";
    const char* port = "13131";

    // parse arguments
    int opt;
    while ((opt = getopt(argc, argv, "h:p:")) >= 0) {
        if (opt == 'h') {
            host = optarg;
        } else if (opt == 'p') {
            port = optarg;
        }
    }

    // look up host and port
    struct addrinfo hints, *ai;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        // use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // use TCP
    hints.ai_flags = AI_NUMERICSERV;
    int r = getaddrinfo(host, port, &hints, &ai);
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(1);
    }

    // connect to server
    int fd = socket(ai->ai_family, ai->ai_socktype, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    r = connect(fd, ai->ai_addr, ai->ai_addrlen);
    if (r < 0) {
        perror("connect");
        exit(1);
    }

    if (optind == argc) {
        usage(0);
    }

    // write arguments
    FILE* f = fdopen(fd, "a+");
    while (optind < argc) {
        if (strcmp(argv[optind], "get") == 0
            && optind + 1 < argc) {
            fprintf(f, "get %s\r\n", argv[optind + 1]);
            optind += 2;

        } else if (strcmp(argv[optind], "set") == 0
                   && optind + 2 < argc) {
            size_t value_len = strlen(argv[optind + 2]);
            fprintf(f, "set %s %zu\r\n",
                    argv[optind + 1], value_len);
            fwrite(argv[optind + 2], 1, value_len, f);
            fprintf(f, "\r\n");
            optind += 3;

        } else if (strcmp(argv[optind], "delete") == 0
                   && optind + 1 < argc) {
            fprintf(f, "delete %s\r\n", argv[optind + 1]);
            optind += 2;

        } else {
            usage(1);
        }
    }

    // shut down writing
    fflush(f);
    shutdown(fd, SHUT_WR);

    // read results
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, f)) {
        fputs(buf, stdout);
    }

    // done
    fclose(f); // This also closes `fd`.
}

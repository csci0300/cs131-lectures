#include "helpers.hh"
#include <netdb.h>
#include <vector>

int main(int argc, char** argv) {
    const char* host = "localhost";
    const char* port = "13131";
    size_t max_conns = 10000;
    raise_file_limit();

    int opt;
    while ((opt = getopt(argc, argv, "h:p:n:")) >= 0) {
        if (opt == 'h') {
            host = optarg;
        } else if (opt == 'p') {
            port = optarg;
        } else if (opt == 'n') {
            max_conns = strtoul(optarg, nullptr, 0);
        }
    }

    struct addrinfo hints, *ai;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    int r = getaddrinfo(host, port, &hints, &ai);
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(1);
    }

    std::vector<int> cfds;
    double start_time = tstamp();
    while (cfds.size() != max_conns) {
        int fd = socket(ai->ai_family, ai->ai_socktype, 0);
        if (fd < 0) {
            perror("socket");
            break;
        }

        r = connect(fd, ai->ai_addr, ai->ai_addrlen);
        if (r < 0) {
            perror("connect");
            break;
        }

        cfds.push_back(fd);
        fprintf(stderr, "\r%zu/%zu connections (%g conns/s)    ",
                cfds.size(), max_conns, cfds.size() / (tstamp() - start_time));
    }

    fprintf(stderr, "\rHolding open %zu connections\n", cfds.size());
    while (1) {
        usleep(1000000);
    }
}

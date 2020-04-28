#include <netdb.h>
#include <time.h>
#include <csignal>
#include <cstdlib>
#include <vector>
#include "helpers.hh"

volatile std::sig_atomic_t done = false;
bool verbose;
int num_threads = 2;

void usage(int exit_status) {
  fprintf(stderr, "Usage: wdbloadtest [-v] [-t NUM_CLIENTS]\n");
  exit(exit_status);
}

void handle_sigint(int signal) {
  assert(signal == SIGINT);
  done = true;
}

void generate_load(int i, const char* host, const char* port) {
  // look up host and port
  struct addrinfo hints, *ai;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;      // use IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // use TCP
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

  // handle Ctrl-C
  std::signal(SIGINT, handle_sigint);

  FILE* f = fdopen(fd, "a+");
  char buf[BUFSIZ];
  srand(time(NULL));

  // create accounts if we're the first thread
  if (i == 0) {
    for (int j = 0; j < num_threads * 2; j++) {
      fprintf(f, "set %d 5\r\n%s\r\n", j, (j % 2) ? "CS131" : "CS030");
    }
    fflush(f);
  }

  int nloops = 0;
  int start = tstamp();
  while (!done) {
    int which = rand() % (num_threads * 2);
    if (which % 2 == 0) {
      fprintf(f, "get %d\r\n", which);
    } else {
      fprintf(f, "exch %d %d\r\n", which, (which + num_threads) % num_threads);
    }
    fflush(f);

    fgets(buf, BUFSIZ, f);

    if (verbose && nloops % 10000 == 0) {
      double cur = tstamp() - start;
      fprintf(stdout, "%f req/s\r\n", ((double) nloops) / cur);
    }

    nloops++;
  }

  // shut down writing
  fflush(f);
  shutdown(fd, SHUT_WR);

  // read results
  while (fgets(buf, BUFSIZ, f)) {
  }

  // done
  fclose(f);  // This also closes `fd`.
}

int main(int argc, char** argv) {
  const char* host = "localhost";
  const char* port = "13131";

  // parse arguments
  int opt;
  while ((opt = getopt(argc, argv, "h:p:vt:")) >= 0) {
    if (opt == 'h') {
      host = optarg;
    } else if (opt == 'p') {
      port = optarg;
    } else if (opt == 'v') {
      verbose = true;
    } else if (opt == 't') {
      num_threads = atoi(optarg);
    }
  }

  std::vector<std::thread*> threads;
  for (int i = 0; i < num_threads; ++i) {
    std::thread* t = new std::thread(generate_load, i, host, port);
    threads.push_back(t);
  }

  for (auto it = threads.begin(); it != threads.end(); it++) {
    (*it)->join();
  }
}

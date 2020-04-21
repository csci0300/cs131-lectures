#include "helpers.hh"

struct hash_item {
    std::string key;
    std::string value;

    hash_item(const std::string& k) {
        this->key = k;
    }
};


#define NBUCKETS 1024
std::list<hash_item> hash[NBUCKETS];


// hash_get(key, create)
//    Looks up `key` in the hashtable, `hash`, and returns
//    the corresponding item. If `key` is not present and
//    `create != 0`, then allocates a new item for `key`,
//    installs it, and returns it. Otherwise, if `key` is
//    not present, returns nullptr.

std::list<hash_item>::iterator hfind(std::list<hash_item>& list,
                                     const char* key) {
    auto it = list.begin();
    while (it != list.end() && it->key != key) {
        ++it;
    }
    return it;
}


void handle_connection(int cfd) {
    FILE* fin = fdopen(cfd, "r");
    FILE* f = fdopen(cfd, "w");

    char buf[BUFSIZ], key[BUFSIZ];
    size_t sz;

    while (fgets(buf, BUFSIZ, fin)) {
        if (sscanf(buf, "get %s ", key) == 1) {
            // find item
            auto b = string_hash(key) % NBUCKETS;
            auto it = hfind(hash[b], key);

            // print value
            if (it != hash[b].end()) {
                fprintf(f, "VALUE %s %zu %p\r\n",
                        key, it->value.length(), &*it);
                fwrite(it->value.data(), 1, it->value.length(), f);
                fprintf(f, "\r\n");
            }
            fprintf(f, "END\r\n");
            fflush(f);

        } else if (sscanf(buf, "set %s %zu ", key, &sz) == 2) {
            // find item; insert if missing
            auto b = string_hash(key) % NBUCKETS;
            auto it = hfind(hash[b], key);
            if (it == hash[b].end()) {
                it = hash[b].insert(it, hash_item(key));
            }

            // set value
            it->value = std::string(sz, '\0');
            fread(it->value.data(), 1, sz, fin);
            fprintf(f, "STORED %p\r\n", &*it);
            fflush(f);

        } else if (sscanf(buf, "delete %s ", key) == 1) {
            // find item
            auto b = string_hash(key) % NBUCKETS;
            auto it = hfind(hash[b], key);

            // remove if found
            if (it != hash[b].end()) {
                void* ptr = &*it;
                hash[b].erase(it);
                fprintf(f, "DELETED %p\r\n", ptr);
            } else {
                fprintf(f, "NOT_FOUND\r\n");
            }
            fflush(f);

        } else if (remove_trailing_whitespace(buf)) {
            fprintf(f, "ERROR\r\n");
            fflush(f);
        }
    }

    if (ferror(fin)) {
        perror("read");
    }
    fclose(fin); // also closes `f`'s underlying fd
    (void) fclose(f);
}


int main(int argc, char** argv) {
    // Usage: ./weensydb [PORT]
    int port = 13131;
    if (argc >= 2) {
        port = strtol(argv[1], nullptr, 0);
        assert(port > 0 && port <= 65535);
    }

    // Prepare listening socket
    int fd = open_listen_socket(port);
    assert(fd >= 0);
    fprintf(stderr, "Listening on port %d...\n", port);

    while (true) {
        // Accept connection on listening socket
        int cfd = accept(fd, nullptr, nullptr);
        if (cfd < 0) {
            perror("accept");
            exit(1);
        }

        // Handle connection
        handle_connection(cfd);
    }
}

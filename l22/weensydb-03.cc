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
std::mutex hash_mutex[NBUCKETS];


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

    char buf[BUFSIZ], key[BUFSIZ], key2[BUFSIZ];
    size_t sz;

    while (fgets(buf, BUFSIZ, fin)) {
        if (sscanf(buf, "get %s ", key) == 1) {
            // find item and fetch value
            auto b = string_hash(key) % NBUCKETS;
            hash_mutex[b].lock();
            auto it = hfind(hash[b], key);

            void* ptr = nullptr;
            std::string value;
            if (it != hash[b].end()) {
                ptr = &*it;
                value = it->value;
            }
            hash_mutex[b].unlock();

            // print value
            if (ptr) {
                fprintf(f, "VALUE %s %zu %p\r\n",
                        key, value.length(), ptr);
                fwrite(value.data(), 1, value.length(), f);
                fprintf(f, "\r\n");
            }
            fprintf(f, "END\r\n");
            fflush(f);

        } else if (sscanf(buf, "set %s %zu ", key, &sz) == 2) {
            // read value
            std::string value = std::string(sz, '\0');
            fread(value.data(), 1, sz, fin);

            // find item; insert if missing
            auto b = string_hash(key) % NBUCKETS;
            hash_mutex[b].lock();
            auto it = hfind(hash[b], key);
            if (it == hash[b].end()) {
                it = hash[b].insert(it, hash_item(key));
            }

            // set value
            it->value = value;
            void* ptr = &*it;
            hash_mutex[b].unlock();

            // print notice
            fprintf(f, "STORED %p\r\n", ptr);
            fflush(f);

        } else if (sscanf(buf, "delete %s ", key) == 1) {
            // find item
            auto b = string_hash(key) % NBUCKETS;
            hash_mutex[b].lock();
            auto it = hfind(hash[b], key);

            // remove if found
            void* ptr = nullptr;
            if (it != hash[b].end()) {
                ptr = &*it;
                hash[b].erase(it);
            }
            hash_mutex[b].unlock();

            // print message
            if (ptr) {
                fprintf(f, "DELETED %p\r\n", ptr);
            } else {
                fprintf(f, "NOT_FOUND\r\n");
            }
            fflush(f);

        } else if (sscanf(buf, "exch %s %s ", key, key2) == 2) {
            // find item
            auto b1 = string_hash(key) % NBUCKETS;
            auto b2 = string_hash(key2) % NBUCKETS;
            if (b1 > b2) {
                hash_mutex[b2].lock();
                hash_mutex[b1].lock();
            } else if (b1 == b2) {
                hash_mutex[b1].lock();
            } else {
                hash_mutex[b1].lock();
                hash_mutex[b2].lock();
            }
            auto it1 = hfind(hash[b1], key);
            auto it2 = hfind(hash[b2], key2);

            // exchange items
            if (it1 != hash[b1].end() && it2 != hash[b2].end()) {
                std::swap(it1->value, it2->value);
                fprintf(f, "EXCHANGED %p %p\r\n", &*it1, &*it2);
            } else {
                fprintf(f, "NOT_FOUND\r\n");
            }
            fflush(f);

            hash_mutex[b1].unlock();
            if (b1 != b2) {
                hash_mutex[b2].unlock();
            }

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
        std::thread t(handle_connection, cfd);
        t.detach();
    }
}

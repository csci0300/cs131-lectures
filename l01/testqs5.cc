#include "qslib.hh"
#include "allowexec.hh"
#include "hexdump.hh"

int main(int argc, char* argv[]) {
    qs_info qsi = parse_arguments(argc, argv);

    std::vector<int> list;
    for (int i = 0; i != qsi.size; ++i) {
        list.push_back(qsi.array[i]);
    }
    ints_print(list);

    if (qsi.execute) {
        // Use the standard algorithm!
        std::sort(list.begin(), list.end());

        ints_print(list);

        assert(ints_sorted(list));
        assert(ints_checksum(list) == qsi.checksum);
    }

    delete[] qsi.array;
}

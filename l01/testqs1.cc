#include "qslib.hh"
#include "allowexec.hh"
#include "hexdump.hh"

void qs(std::list<int>& list) {
    if (list.size() > 1) {
        int pivot = list.front();

        // move pivot element into middle
        std::list<int> middle;
        middle.splice(middle.end(), list, list.begin());

        // destructive partition:
        // remove greater elements into a new list
        std::list<int> right;
        for (auto it = list.begin(); it != list.end(); ) {
            auto next = std::next(it);
            if (*it >= pivot) {
                right.splice(right.end(), list, it);
            }
            it = next;
        }

        // recurse
        qs(list);
        qs(right);

        // destructive append
        list.splice(list.end(), middle);
        list.splice(list.end(), right);
    }
}

int main(int argc, char* argv[]) {
    qs_info qsi = parse_arguments(argc, argv);

    std::list<int> list;
    for (int i = 0; i != qsi.size; ++i) {
        list.push_back(qsi.array[i]);
    }
    ints_print(list);

    if (qsi.execute) {
        qs(list);

        ints_print(list);

        assert(ints_sorted(list));
        assert(ints_checksum(list) == qsi.checksum);
    }

    delete[] qsi.array;
}

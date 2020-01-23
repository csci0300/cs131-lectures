#include "qslib.hh"
#include "allowexec.hh"
#include "hexdump.hh"

void qs(int* first, int* last) {
    size_t size = last - first;
    if (size > 1) {
        // move pivot to end
        int pivot = *first;
        std::swap(*(last - 1), *first);

        // destructive partition
        int* left = first;
        int* right = last - 1;
        // Invariants:
        // * all elements in [first, left) are `< pivot`
        // * all elements in [right, last - 1) are `>= pivot`
        // At each step, swap elements or move pointers
        // while preserving the invariants.
        while (left < right) {
            if (*left <= pivot) {
                ++left;
            } else if (*(right - 1) > pivot) {
                --right;
            } else {
                std::swap(*left, *(right - 1));
                ++left;
                --right;
            }
        }
        // move pivot to middle where it belongs
        std::swap(*left, *(last - 1));

        // recurse, leaving out pivot
        qs(first, left);
        qs(left + 1, last);
    }
}


int main(int argc, char* argv[]) {
    qs_info qsi = parse_arguments(argc, argv);

    std::vector<int> list;
    for (int i = 0; i != qsi.size; ++i) {
        list.push_back(qsi.array[i]);
    }
    ints_print(list);

    if (qsi.execute) {
        qs(list.data(), list.data() + list.size());

        ints_print(list);

        assert(ints_sorted(list));
        assert(ints_checksum(list) == qsi.checksum);
    }

    delete[] qsi.array;
}

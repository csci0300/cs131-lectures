#include "qslib.hh"
#include "allowexec.hh"
#include "hexdump.hh"

std::list<int> qs(std::list<int>& list) {
    if (list.empty()) {
        return list;
    } else {
        int pivot = list.front();             // first element
        auto rest = std::next(list.begin());  // rest of list

        // copy pivot element into `middle`
        std::list<int> middle;
        std::copy(list.begin(), rest, std::back_inserter(middle));

        // partition
        std::list<int> left;
        std::copy_if(rest, list.end(), std::back_inserter(left),
                     [=] (int i) { return i < pivot; });

        std::list<int> right;
        std::copy_if(rest, list.end(), std::back_inserter(right),
                     [=] (int i) { return i >= pivot; });

        // recurse and append
        return ints_append(ints_append(qs(left), middle),
                           qs(right));
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
        list = qs(list);

        ints_print(list);

        // check that the collection is sorted
        assert(ints_sorted(list));
        // check that the sorted collection contains the same data
        // (this can be fooled, but it's better than nothing!)
        assert(ints_checksum(list) == qsi.checksum);
    }

    delete[] qsi.array;
}

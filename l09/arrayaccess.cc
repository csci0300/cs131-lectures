#include "qslib.hh"

int main(int argc, char* argv[]) {
    qs_info qsi = parse_arguments(argc, argv);
    assert(strcmp(qsi.pattern, "magic") != 0);

    // initialize data array
    int* data = new int[qsi.size];
    initialize_up(data, qsi.size);

    printf("accessing %d integers %u times in %s order:\n", qsi.size, qsi.repeats, qsi.pattern);
    ints_print(qsi.array, qsi.size);

    // sum elements of `data` array;
    // access array in order defined by `-r/-u/-d` argument
    double start = timestamp();
    unsigned sum = 0;
    for (unsigned int rep = 0; rep < qsi.repeats; ++rep) {
      for (int i = 0; i != qsi.size; ++i) {
          int data_index = qsi.array[i];
          assert(data_index >= 0 && data_index < qsi.size);
          sum += (unsigned) data[data_index];
      }
    }

    // check the checksum
    unsigned long lsize = qsi.size;
    assert(sum == (unsigned) ((lsize * (lsize - 1)) / 2) * qsi.repeats);
    printf("OK in %.06f sec!\n", timestamp() - start);

    delete[] qsi.array;
    delete[] data;
}

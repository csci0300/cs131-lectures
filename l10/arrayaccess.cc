#include "helperlib.hh"

int main(int argc, char* argv[]) {
    arg_info cfg = parse_arguments(argc, argv);

    // initialize data array
    int* data = new int[cfg.size];
    initialize_up(data, cfg.size);

    printf("accessing %d integers %u times in %s order:\n",
           cfg.size, cfg.repeats, cfg.pattern);
    ints_print(cfg.array, cfg.size);

    // sum elements of `data` array;
    // access array in order defined by `-r/-u/-d` argument
    double start = timestamp();
    unsigned sum = 0;
    for (unsigned int rep = 0; rep < cfg.repeats; ++rep) {
      for (int i = 0; i != cfg.size; ++i) {
          int data_index = cfg.array[i];
          assert(data_index >= 0 && data_index < cfg.size);
          sum += (unsigned) data[data_index];
      }
    }

    // check the checksum to ensure we actually touched all memory
    unsigned long lsize = cfg.size;
    assert(sum == (unsigned) ((lsize * (lsize - 1)) / 2) * cfg.repeats);
    printf("OK in %.06f sec!\n", timestamp() - start);

    delete[] cfg.array;
    delete[] data;
}

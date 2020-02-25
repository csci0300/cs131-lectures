#include <vector>
#include <cstdio>
#include <map>

int main() {
  // declares a heap-allocated standard library vector of ints
  // similar to strvec's vector_t, but in C++. data on the heap!
  std::vector<int>* v = new std::vector<int>();

  // append 5 numbers to the vector
  v->push_back(41);
  v->push_back(42);
  v->push_back(43);
  v->push_back(44);
  v->push_back(45);

  // C-style iteration with a loop index works
  for (unsigned int i = 0; i < v->size(); i++) {
    printf("%d\n", v->at(i));
  }

  // below is the same, but uses C++ iterators
  for (auto it = v->begin(); it != v->end(); it++) {
    printf("%d\n", *it);
  }

  // frees the heap memory used for the vector
  delete v;

  // stack-allocated key -> value map; data is on the heap!
  // (this allocates memory internally)
  std::map<const char*, int> my_map;
  // add entries
  my_map.emplace("alice", 12);
  my_map.emplace("bob", 42);

  printf("alice -> %d\n", my_map.at("alice"));
  printf("bob -> %d\n", my_map.at("bob"));

  // iterate over the map using a C++ iterator
  // the "auto" syntax is identical to:
  // for (std::map<char*, int>::iterator it = my_map.begin(); it != my_map.end(); it++) {
  // ... we're just leaving the compiler to figure out the iterator type for us.
  for (auto it = my_map.begin(); it != my_map.end(); it++) {
    // *it is a std::pair<key type, value type>, which has members `first` and `second`
    printf("%s -> %d\n", it->first, it->second);
  }

  // std::string is a dynamic, heap-allocated string that you can grow and shrink
  std::string my_string("hello");
  my_string.append(" world!");

  // to print a std::string, use .c_str() on it
  printf("%s\n", my_string.c_str());
}

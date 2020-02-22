# Demo code from Section 4 (C++)

This section focused on C++, its object-oriented features, and thes standard
library data structures that might be useful for Project 2.

To compile, use:
```
$ make
```

`cpp1.c` demonstrates how C++ classes work: you can think of them as C
structures with associated methods (functions operating on instances of the
class, like in Java).

`cpp2.c` demonstrates several handy standard library data structures:
std::vector (a dynamically resizable array, like you built in Project 1)
and std::map (a key-value dictionary). It also introduces the notion of C++
iterators, which make it easier to iterate over data structures that do not
support straightforward access by numeric indexes (such as an std::map).

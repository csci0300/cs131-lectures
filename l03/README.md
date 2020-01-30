Lecture 3
=========

Data representation, Pointers, Strings, and Arrays
--------------------------------------------------

Today, we continued to use the `mexplore` program and variations of it to
explore data representation and distinguish storage lifetimes.

To build the code in this folder, run:

```
$ make
```
(You will need the `clang` compiler for this. If you get an error, install
it using `sudo apt-get install clang` in the course VM. We use clang because
it chooses to place data at addresses that make it easy to see the memory
segments; `gcc`'s address choices are less clear. If you want to try that,
change `CC = clang` to `CC = gcc` in `Makefile`.)

Then you can run `./mexplore` to see the address (leftmost), hexadecimal
bytes at that address (middle), and their translation into ASCII letters
(right).

* `mexplore` is the same as the program we used last time.
* `mexplore-with-dynamic` adds dynamically-allocated memory obtained via
  `malloc()` and shows how the lifetime of such memory extends beyond the
  end of the scope that defined the variable.
* `mexplore-string` moves from single characters to strings and illustrates
  how strings are just sequences of bytes in memory, with a NUL byte
  terminating the string.
* `mexplore-undefined` explores what the contents of dynamically allocated
  memory are when the program first obtains that memory. Uncomment the
  commented lines to see (perhaps) a surprise!
* `mexplore-array` explores the memory representation of arrays.

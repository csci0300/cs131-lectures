CS 131 Lecture 1: Overview and Memory
=====================================

This lecture is our teaser lecture, designed to introduce the course and
data representation in memory, a key concept for understanding the magic of
computer systems. The lecture aims to pique your interest and to introduce
interesting directions — but does not necessarily to explain the outcomes
or all syntax we see. We'll be investigating the details of these and other
experiments for the rest of the class.

Type `make` to build the programs in this directory. This should work on
the department machines and in your course VM (see Lab 0 for setup
instructions).

Quicksort
---------

We investigated a number of different quicksort implementations as
systems programs.

Quicksort on Wikipedia: https://en.wikipedia.org/wiki/Quicksort

* `qs.arr`: A Pyret quicksort implementation.

* `qs.ml`: An OCaml quicksort function.

All the following are in C++:

* `testqs0.cc`, `testqs1.cc`: List-based quicksorts (like OCaml),

* `testqs2.c` through `testqs4.c`: Array-based quicksorts in .

* `testqs5.c`: Standard library quicksort (array-based).

Type `make` to build programs `testqs0` through `testqs6`. Options for
these programs are:

* `./testqsX -r [N]`: The array contains `N` random ints. Default `N`
  is 6.
* `./testqsX -u [N]`: The array is initially sorted.
* `./testqsX -d [N]`: The array is initially reverse-sorted.
* `./testqsX -m [N]`: The array contains the numbers 1,...,`N` in a
  magic evil order.

Executions to try:

* `./testqs0 -r 10`
* `./testqs0 -r 10000000`
* `make SANITIZE=1; ./testqs5 -m 100000`
* `./testqs3 -u 100000` vs. `./testqs4 -u 100000`

Try `time ./testqsX` to see how long an execution takes.

Further reading: "Implementing Quicksort Programs", Robert Sedgewick,
Communications of the ACM 21(10), October 1978;
http://www.csie.ntu.edu.tw/~b93076/p847-sedgewick.pdf

"Engineering a Sort Function", Jon L. Bentley and M. Douglas McIlroy,
Software---Practice and Experience 23(11), November 1993;
http://www.skidmore.edu/~meckmann/2009Spring/cs206/papers/spe862jb.pdf


`add` and `addin`
-----------------

Run `./add 2 2` to add 2 and 2.

The `add` function’s definition is located in `addf.c`. Check out
`addf-examples.c` for some alternate definitions that work too
(amazingly).

Run `./addin FILE OFFSET A B` to add `A` and `B`, using the “add function”
located in `FILE` at byte `OFFSET`. For instance, try `./addin addf.o 64 2 2`.

Use `objdump -S addf.o` to look at the instructions in `addf.o`.

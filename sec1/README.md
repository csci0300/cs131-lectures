# Demo code from C Gearup Section

`examples.c` contains the example we built up during our discussion.
The goal of `f()` is to return two integers, and we are using dynamic
memory and pointers to achieve this.

To compile, use:
```
$ clang -o examples examples.c -g
```
or
```
$ gcc -o examples examples.c -g
```
In the section, we used `clang` because it makes the difference between
stack addresses (in the automatic segment of memory) and heap addresses
(in the dynamic segment of memory) more obvious.

Some questions we resolved, for reference:
* Why can't I just allocate the integers as local variables in `f()` and
  return them?
* Why can't I return a pointer to a local variable?
* Where is the address of the `malloc`-ed memory stored? How does that
  information get back to `main()`?
* How would I return a substring of a string from `f()`? (not included in
  the example)
* How does pointer arithmetic work?
* How are pointers and arrays related?

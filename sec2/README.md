# Demo code from C Gearup Section 2

`examples.c` contains the example we built up during our discussion.

To compile, use:
```
$ clang -o examples examples.c -g
```
or
```
$ gcc -o examples examples.c -g
```

We first discussed how the array notation on pointers is the same as pointer
arithmetic with the example of two pointers into a heap-allocated range of
10 integers.

In the second part, we looked at the syntax of `typedef`, and at how different
notations to access members of a struct (such as a `list_node_t`) amount to
the same thing (a byte offset from the address of the struct).

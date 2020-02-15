# Demo code from Section 3 (Address Sanitizers)

`wild-write{1,2}.c` contain the examples of errors that the address
sanitizer can and cannot catch that we constructed during our discussion.

To compile, use:
```
$ make
```

Both `wild-write1.c` and `wild-write2.c` contain so-called **wild writes**,
where a program writes beyond the end of a valid heap allocation (also
called a "heap buffer overflow"). These are devious bugs because the program
may seem to work fine when you run it, but wild writes can actually
silently corrupt your memory.

In `wild-write1.c`, using the address sanitizer helps us find the problem
(compile with `-fsanitize=address`).

But in `wild-write2.c`, the address sanitizer cannot help us because the
write _happens_ to touch a valid allocation. This illustrates that passing
the address sanitizer is a necessary condition for a program free of memory
bugs, but it's not a sufficient condition; a program that passes the
sanitizer can still have memory bugs in it.

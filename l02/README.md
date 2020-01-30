Lecture 2
=========

Objdump
-------

We used the `objdump` utility today to look at compiled
code. `objdump` can produce many different kinds of output, depending
on the options you give it.  Some common ones:

* `objdump -s FILE.o` (or `objdump -s EXECUTABLEFILE`): Print the
  assembly instructions in the object file or executable.
* `objdump -S FILE.o`: Print the instructions, interleaved with the source
  files that generated those instructions. Only works if the object file or
  executable was compiled with debugging support (which all your files will
  be).

Since `objdump` usually generates a lot of output, it’s useful to send
its output to a “pager” program, so you can scroll through that
output. We prefer `less`:

    $ objdump -s FILE.o | less

Within `less`, type spacebar to go forward a screen, `b` to go back a
screen, and `q` to quit.

Many command line programs have useful help available


Data representation
-------------------

Use the `mexplore` program to explore data representation and
distinguish storage lifetimes.

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

Play around with this and try a few things!

* Assign the number 65 to `global_ch` instead of 'A'. What happens?
* Create a function `g()` that defines another two local `char` variables
  and calls `hexdump()` on their address. At what address are they stored?
  What memory segment is that address in?

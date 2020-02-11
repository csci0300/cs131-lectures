CC = clang
PROGRAMS = mexplore-structalign ubexplore.noopt ubexplore.opt ubexplore2.noopt ubexplore2.opt signed-int

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%.opt.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O3 $(DEPCFLAGS) -o $@ -c $<

%.noopt.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

mexplore-structalign signed-int: %: %.o hexdump.o
	$(CC) $(CFLAGS) $(LDFLAGS) -O3 -o $@ $^

ubexplore.noopt ubexplore2.noopt: %.noopt: %.noopt.o hexdump.o
	$(CC) $(CFLAGS) $(LDFLAGS) -O0 -o $@ $^

ubexplore.opt ubexplore2.opt: %.opt: %.opt.o hexdump.o
	$(CC) $(CFLAGS) $(LDFLAGS) -O3 -o $@ $^

clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean

CC = clang
O = 0
PROGRAMS = mexplore mexplore-with-dynamic mexplore-string mexplore-uninitialized mexplore-array
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

mexplore mexplore-with-dynamic mexplore-string mexplore-uninitialized mexplore-array: %: %.o hexdump.o
	$(CC) $(CFLAGS) $(LDFLAGS) -O0 -o $@ $^

clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean

PROGRAMS = bbuffer-basic bbuffer-scoped bbuffer-mutex bbuffer-cond

all: $(PROGRAMS)

RUSTPROGRAMS = rust-demo rust-thread

rust: $(RUSTPROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

O = 2
PTHREAD = 1
include ../common/rules.mk
CXXFLAGS += -g

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%.noopt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) -O0 -o $@ -c $<

%: %.o
	$(CXX) $(CXXFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS)

%.noopt: %.noopt.o
	$(CXX) $(CXXFLAGS) -O0 -o $@ $^ $(LDFLAGS) $(LIBS)

rust-%: rust-%.rs
	rustc $<

clean:
	rm -f $(ALLPROGRAMS) *.o data
	rm -f $(RUSTPROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PRECIOUS: %.noopt.o
.PHONY: all clean

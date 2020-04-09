PROGRAMS = incr-basic incr-basic.noopt incr-atomic \
           incr-mutex bbuffer-basic bbuffer-scoped \
           bbuffer-mutex bbuffer-cond

all: $(PROGRAMS)

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


clean:
	rm -f $(ALLPROGRAMS) *.o data
	rm -rf $(DEPSDIR) *.dSYM

.PRECIOUS: %.noopt.o
.PHONY: all clean

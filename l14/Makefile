PROGRAMS = fork1 fork2 fork2b fork3 forkmix-syscall forkmix-stdio

all: $(PROGRAMS)

O = 2
include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	@$(call xrun,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

$(PROGRAMS): %: %.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)


clean:
	rm -f $(PROGRAMS) *.o data
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean

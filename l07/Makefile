ASMS := $(patsubst %.c,%.s,$(sort $(wildcard asm[0-9][0-9].c)))
ASM_OBJECTS := $(patsubst %.s,%.o,$(ASMS))
ASM_PROGRAMS := $(shell grep -l main $(wildcard asm[0-9][0-9].s asm[0-9][0-9].c) | sed 's/\.[cs]*//' | sort -u)
DEFAULT_ASM_CXXFLAGS = -O1
DEFAULT_ASM_CXXFLAGS_DEBUG = -g $(DEFAULT_ASM_CXXFLAGS)

PROGRAMS = $(ASM_PROGRAMS)

all: $(ASMS) $(PROGRAMS)

asm: cleanasm $(ASMS) $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

O = 1
include ../common/rules.mk

UNSAFEFLAGS := -U_FORTIFY_SOURCE -fno-stack-protector $(if $(ISLINUX),-no-pie,)

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%.noopt.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) -O0 -o $@ -c $<

%.opt.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) -O3 -o $@ -c $<

%.unsafe.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(UNSAFEFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%.unsafenoopt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(UNSAFEFLAGS) $(CXXFLAGS) $(DEPCFLAGS) -O0 -o $@ -c $<


$(ASM_OBJECTS): %.o: %.s $(BUILDSTAMP)
	$(call run,$(CC) -o $@ -c,ASSEMBLE,$<)

%.s: %.c Makefile
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CXXFLAGS="`echo "$(CXXFLAGS)" | sed 's/ *-g */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CXXFLAGS)"; fi; \
	  $(call xrun,$(CXX) $$CXXFLAGS $$ARGS -o $@ -S $<,COMPILE -S $$ARGS $<) && { $(call cleanasm,$@); }

%.unsafe.s: %.c Makefile
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CXXFLAGS="`echo "$(UNSAFEFLAGS) $(CXXFLAGS)" | sed 's/ *-g */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CXXFLAGS)"; fi; \
	  $(call xrun,$(CXX) $$CXXFLAGS $$ARGS -o $@ -S $<,COMPILE -S $$ARGS $<) && { $(call cleanasm,$@); }

$(ASM_PROGRAMS): %: %.s
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CXXFLAGS="`echo "$(CXXFLAGS)" | sed 's/ *-g */ /;s/ *-std=[^ ]* */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CXXFLAGS)"; fi; \
	  $(call xrun,$(CXX) $$CXXFLAGS $$ARGS -o $@ $<,ASSEMBLE $@)

ubexplore.opt ubexplore2.opt: %: %.o hexdump.opt.o
	$(CC) $(CFLAGS) $(DEPCFLAGS) -O3 -g -o $@ $^

ubexplore.noopt ubexplore2.noopt: %: %.o hexdump.noopt.o
	$(CC) $(CFLAGS) $(DEPCFLAGS) -O0 -g -o $@ $^

mexplore-structalign signed-int: %: %.o hexdump.o
	$(CC) $(CFLAGS) $(DEPCFLAGS) -O0 -g -o $@ $^

allasmc.txt: $(wildcard asm*.c) always
	for i in asm*.c; do echo $$i; echo ========; cat $$i; echo; echo; done > $@

allasms.txt: $(patsubst %.c,%.s,$(wildcard asm*.c)) always
	for i in asm*.s; do echo $$i; echo ========; cat $$i; echo; echo; done > $@


clean:
	rm -f $(ALLPROGRAMS) *.o

cleanasm: clean
	rm -f $(patsubst %.c,%.s,$(wildcard asm*.c))

.PHONY: all clean cleanasm asm

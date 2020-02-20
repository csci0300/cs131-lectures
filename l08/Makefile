PROGRAMS = attackme attackme.unsafe call04f backwards asm06.o
#	$(sort $(patsubst %.c,%,$(wildcard call[0-9]f.c)))

CF_ASMS := $(patsubst %.c,%.s,$(sort $(wildcard controlflow[0-9][0-9].c)))
CALL_ASMS := $(patsubst %.c,%.s,$(sort $(wildcard call[0-9][0-9].c)))
CALL_ASM_OBJECTS := $(patsubst %.s,%.o,$(CALL_ASMS))
ASM_PROGRAMS := $(shell grep -l main $(wildcard call[0-9][0-9].s call[0-9][0-9].c) | sed 's/\.[cs]*//' | sort -u)
DEFAULT_ASM_CXXFLAGS = -O1
DEFAULT_ASM_CXXFLAGS_DEBUG = -g $(DEFAULT_ASM_CXXFLAGS)

-include conf.mk

all: asm $(PROGRAMS)

asm: cleanasm $(CF_ASMS) $(CALL_ASMS)

ALLPROGRAMS = $(PROGRAMS)

O = 2
include ../common/rules.mk

UNSAFEFLAGS := -U_FORTIFY_SOURCE -fno-stack-protector $(if $(ISLINUX),-no-pie,)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

attackme.o: attackme.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) -O1 -o $@ -c $<

%.unsafe.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(UNSAFEFLAGS) $(CXXFLAGS) -O1 $(DEPCFLAGS) -o $@ -c $<

%.unsafe.s: %.cc Makefile
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CXXFLAGS="`echo "$(UNSAFEFLAGS) $(CXXFLAGS) -O1" | sed 's/ *-g */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CXXFLAGS)"; fi; \
	  $(call xrun,$(CXX) $$CXXFLAGS $$ARGS -o $@ -S $<,COMPILE -S $$ARGS $<) && { $(call cleanasm,$@); }

$(CALL_ASM_OBJECTS): %.o: %.s $(BUILDSTAMP)
	$(call run,$(CC) -o $@ -c,ASSEMBLE,$<)

call04f: call04f.c call04.c
	$(CC) $(CFLAGS) -fomit-frame-pointer -O1 -o $@ $^

backwards: backwards.c asm06.c
	$(CC) $(CFLAGS) -fomit-frame-pointer -O1 -o $@ $^

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

attackme: attackme.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)

attackme.unsafe: attackme.unsafe.o
	@$(call xrun,$(CXX) $(CXXFLAGS) $(UNSAFEFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS),LINK $@)


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

cleanasm: clean
	rm -f $(patsubst %.c,%.s,$(wildcard controlflow*.c))
	rm -f $(patsubst %.c,%.s,$(wildcard call*.c))

.PHONY: all clean cleanasm asm

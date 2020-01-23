PROGRAMS = add addin
TESTQSPROGRAMS = testqs0 testqs1 testqs2 testqs3 testqs4 testqs5
ALLPROGRAMS = $(PROGRAMS) $(TESTQSPROGRAMS)

all: $(ALLPROGRAMS)

include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

testaccess: testaccess.o qslib.o allowexec.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testinsert0: testinsert0.o qslib.o allowexec.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testinsert1: testinsert1.o qslib.o allowexec.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testinsert2: testinsert1.o qslib.o allowexec.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

add: add.o addf.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

addin: addin.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

addf.o: addf.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -fomit-frame-pointer -o $@ -c $<

testqs: $(TESTQSPROGRAMS)

testqs0: testqs0.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testqs1: testqs1.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testqs2: testqs2.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testqs3: testqs3.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testqs4: testqs4.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

testqs5: testqs5.o qslib.o allowexec.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR) qs.jarr qsml qs.cmi qs.cmo *.class

.PHONY: all clean

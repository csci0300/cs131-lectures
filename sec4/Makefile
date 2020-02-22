.PHONY: all clean

CXXFLAGS = -g -fsanitize=address

all: cpp1 cpp2

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f cpp1 cpp2

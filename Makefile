all: libmsr.so msr_test
CXXFLAGS=-std=c++11 -g
libmsr.so: msr.cpp msr.hpp Makefile
	g++ -shared -fPIC msr.cpp -o libmsr.so $(CXXFLAGS)
msr_test: libmsr.so msr_test.cpp
	g++ -o msr_test msr_test.cpp -lmsr $(CXXFLAGS) -L.
clean:
	rm -f libmsr.so msr_test *.o

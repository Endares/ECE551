test1: test1.o
	g++ -o test1 test1.o

test1.o: test1.cpp poly.hpp
	g++ -std=c++17 -pedantic -Wall -c test1.cpp

clean:  
	rm -f test1 *.o *.cpp~
.PHONY: clean

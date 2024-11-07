test3: test3.o
	g++ -o test3 test3.o

test3.o: test3.cpp poly.hpp
	g++ -std=c++17 -pedantic -Wall -c test3.cpp

clean:  
	rm -f test3 *.o *.cpp~
.PHONY: clean

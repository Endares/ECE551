test2: test2.o
	g++ -o test2 test2.o

test2.o: test2.cpp poly.hpp
	g++ -std=c++17 -pedantic -Wall -c test2.cpp

clean:  
	rm -f test2 *.o *.cpp~
.PHONY: clean

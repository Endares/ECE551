code: code.o
	g++ -o code code.o

test.o: code.cpp
	g++ -std=c++17 -pedantic -Wall -c code.cpp

clean:  
	rm -f code *.o *.cpp~
.PHONY: clean

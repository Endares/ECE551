myProgram: code.o
	g++ -o myProgram code.o 

code.o: code.cpp
	g++ -std=c++17 -pedantic -Wall -c code.cpp

clean:  
	rm -f myProgram *.o *.cpp~
.PHONY: clean

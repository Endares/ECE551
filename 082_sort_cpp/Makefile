sortLines: sortLines.o
	g++ -o sortLines sortLines.o

sortLines.o: sortLines.cpp
	g++ -std=c++17 -pedantic -Wall -c sortLines.cpp

clean:  
	rm -f sortLines *.o *.cpp~
.PHONY: clean

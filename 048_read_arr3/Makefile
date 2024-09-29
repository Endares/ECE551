myProgram: test.o
	gcc -o myProgram test.o
test.o: test.c
	gcc -std=gnu99 -pedantic -Wall -c test.c

clean:
	rm -f myProgram *.o *.c~
.PHONY: clean

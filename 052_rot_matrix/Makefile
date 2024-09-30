rotateMatrix: rotateMatrix.o
	gcc -o rotateMatrix rotateMatrix.o
rotateMatrix.o: rotateMatrix.c
	gcc -std=gnu99 -pedantic -Wall -c rotateMatrix.c

clean:
	rm -f rotateMatrix *.o *.c~
.PHONY: clean

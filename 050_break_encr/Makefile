breaker: breaker.o
	gcc -o breaker breaker.o
breaker.o: breaker.c
	gcc -std=gnu99 -pedantic -Wall -c breaker.c
clean:
	rm -f breaker *.o *.c~
.PHONY: clean

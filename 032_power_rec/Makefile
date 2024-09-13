myProgram: power.o test-power.o
	gcc -o myProgram power.o test-power.o
power.o: power.c
	gcc -std=gnu99 -pedantic -Wall -c power.c
test-power.o: power.c
	gcc -std=gnu99 -pedantic -Wall -c test-power.c

clean:
	rm -f myProgram *.o *.c~

.PHONY: clean

CFLAGS = -Wall -std=gnu99 -pedantic

test: test.o
	gcc $(CFLAGS) -o test test.o

test.o: test.c
	gcc -Wall -std=gnu99 -pedantic -c test.c


.PHONY: clean

clean:
	rm -f test test.o


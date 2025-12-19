#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void check(unsigned x, unsigned y, unsigned expected) {
	unsigned ans = power(x, y);
	if (ans != expected) {
		printf("Not passed!\n");
		exit(EXIT_FAILURE);
	}
}	

int main(void) {
	check(9, 0, 1);
	check(1, 0, 1);
	check(1111, 0, 1);
	check(0, 1, 0);
	check(1, 1, 1);
	check(0, 2, 0);
	check(1, 2, 1);
	check(1, 1212, 1);
	check(3, 2, 9);
	check(10, 5, 100000);
	check(2, 16, 65536);
	check(0, 0, 1);
	check(2002, 3, 8024024008);
	check(3, 5, 243);
}

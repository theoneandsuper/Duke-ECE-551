#include <stdio.h>
#include <stdlib.h>

#include <limits.h>


size_t maxSeq(int * array, size_t n);

void check(int * array, size_t n, size_t expected) {
	if (expected != maxSeq(array, n)) {
		exit(EXIT_FAILURE);
	}		
}

int main(){
	int a0[10] = {1, 1, 2, 2, 2, 3, 4, 5, 7, 9};
	int a1[1] = {7};
	int a2[7] = {10, 9, 8, 7, 6, 5, 4};
	int a3[7] = {0, 0, 0, 0, 0, 0, 0};
	int a4[7] = {1, 2, 3, 4, 5, 6, 7};
	int *a5 = NULL;
	int a6[7] = {-7, -6, -5, -4, -3, -2, -1};
	int a7[3] = {1, 0, 2};
	int a8[3] = {INT_MAX, 7, INT_MIN};
	int a9[7] = {1, 2, 3, 4, 3, 2, 1};

	check(a0, 10, 6);
	check(a1, 1, 1);
	check(a2, 7, 1);
	check(a3, 7, 1);
	check(a4, 7, 7);
	check(a5, 0, 0);
	check(a6, 7, 7);
	check(a7, 3, 2);
	check(a8, 3, 1);
	check(a9, 7, 4);
	exit(EXIT_SUCCESS);
	
}

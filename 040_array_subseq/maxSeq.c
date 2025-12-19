#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n) {
	if (n == 0) {
		return 0;
	}

	size_t best = 1;
	size_t temp  = 1;

	for (size_t i = 1; i < n; i++) {
		if (array[i] > array[i - 1]) {
			temp++;
		} 
		else {
			if (temp > best) {
				best = temp;
			}
			temp = 1;
		}
	}
	if (temp > best) {
		best = temp;
	}
	return best;
}	

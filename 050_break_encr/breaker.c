#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int breaker(FILE *f) {
	long freq[26] = {0};;

	int temp;
	while ((temp = fgetc(f)) != EOF) {
		unsigned char utemp = (unsigned char)temp;
		if (isalpha(utemp)) {
			utemp = (unsigned char)tolower(utemp);
			freq[utemp - 'a']++;
		}
	}

	long best_count = 0;
	int best_index = 0;

	for (int i = 0; i < 26; i++) {
		if (freq[i] > best_count) {
			best_count = freq[i];
			best_index = i;
		}
	}

	if (best_count == 0) {
		return -1;
	}

	int key = (best_index - ('e' - 'a') + 26) % 26;
	return key;
}	

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "InputFileName?\n");
		return EXIT_FAILURE;
	}

	FILE *f = fopen(argv[1], "r");

	if (f == NULL) {	
		perror("Can't really open file");
		return EXIT_FAILURE;
	}

	int key = breaker(f);

	if (fclose(f) != 0) {
  		perror("Can't close the input file!");
   		return EXIT_FAILURE;
	}
	
	if (key < 0 || key >= 26) { 
		fprintf(stderr,	"Zero letters!\n");
		return EXIT_FAILURE;			
	}

	printf("%d\n", key);
	return EXIT_SUCCESS;
}	
		
		

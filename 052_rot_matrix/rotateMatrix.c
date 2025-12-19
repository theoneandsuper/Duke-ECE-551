#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
        	fprintf(stderr, "Argument number wrong");
       		exit(EXIT_FAILURE);
    	}

    	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		fprintf(stderr, "Nothing");
		return EXIT_FAILURE;
	}

	char matrix[10][10];	

	char holder[128];

	for (int i = 0; i < 10; i++) {
		char *line = fgets(holder, sizeof(holder), fp);
		
		if (line == NULL) {
    			fprintf(stderr, "Error: line %d missing\n", i+1);
    			fclose(fp);
    			exit(EXIT_FAILURE);
		}

		size_t len = strlen(holder);

		if (holder[len-1] == '\n') {
            		if (len != 11) {
                		fprintf(stderr, "Line %d characters wrong\n", i+1);
                		fclose(fp);
                		exit(EXIT_FAILURE);
           		}
            		holder[len-1] = '\0'; 
       		} 
		else {
                	if (len != 10) {
                		fprintf(stderr, "Wrong character nums\n");
                		fclose(fp);
                		exit(EXIT_FAILURE);
           		}
        	}

		for (int j = 0; j < 10; j++) {
			matrix[i][j] = holder[j];
		}
	}


	char *extra = fgets(holder, sizeof(holder), fp);	

	if (extra != NULL) {
		fprintf(stderr, "Error!");	
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	fclose(fp);

	for (int j = 0; j < 10; j++) {
		for (int i = 10 - 1; i >= 0; i--) {
			putchar(matrix[i][j]);
		}
		putchar('\n');
	}

	return EXIT_SUCCESS;
}	



	

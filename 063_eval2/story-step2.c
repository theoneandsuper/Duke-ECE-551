#include "provided.h"
#include "rand_story.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Argument number wrong!\n");
		return EXIT_FAILURE;
	}

	FILE * f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("Better check if this really exists");
		return EXIT_FAILURE;
	}

	catarray_t category_list;
	parse_category_file(f, &category_list);

	fclose(f);

	printWords(&category_list);

	free_category_list(&category_list);

	return EXIT_SUCCESS;
}

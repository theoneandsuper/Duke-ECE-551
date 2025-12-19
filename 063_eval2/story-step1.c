#include "rand_story.h"

int main(int argc, char * argv[]) {
	//must have two arguments
	if (argc != 2) {
		fprintf(stderr, "Argument number doesnt match!\n");
		return EXIT_FAILURE;
	}

	FILE * f = fopen(argv[1], "r");
	//very basic already, chekcing if this file exists
	if (f == NULL) {
		perror("Go chekc if this file really exist!");
		return EXIT_FAILURE;
	}

	process_story_file(f);
	fclose(f);
	return EXIT_SUCCESS;
}

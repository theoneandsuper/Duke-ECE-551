#include "rand_story.h"
#include "provided.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	int if_can_be_reused = 1;
	const char *words_file = NULL;
	const char *story_file = NULL;

	if (argc == 3) {
		words_file = argv[1];
		story_file = argv[2];
	}
	else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
		if_can_be_reused = 0;
		words_file = argv[2];
		story_file = argv[3];
	}
	else {
		fprintf(stderr, "argument number wrong or format incorrect!\n");
		return EXIT_FAILURE;
	}

	return story_process_main(words_file, story_file, if_can_be_reused);
}

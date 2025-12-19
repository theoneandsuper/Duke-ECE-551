#include "rand_story.h"
#include "provided.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Argument number doesn't match!\n");
		return EXIT_FAILURE;
	}
	return story_process_main(argv[1], argv[2], 1);
}

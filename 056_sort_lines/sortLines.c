#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void work_it_out(FILE *f);

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
	if (argc == 1) {
		FILE * f = stdin;
		if (f == NULL) {
			perror("Something wrong with the file!");
			return EXIT_FAILURE;
		}
		work_it_out(f);
	}
	else {
		for (size_t i = 1; i < argc; i++) {
			FILE * f = fopen(argv[i], "r");
			if (f == NULL) {
				perror("Something wrong with the file!");
				return EXIT_FAILURE;
			}
			work_it_out(f);
			if (fclose(f) != 0) {
				perror("can't close file");
				return EXIT_FAILURE;
			}
		}
	}		
	return EXIT_SUCCESS;
}

void work_it_out(FILE *f) {
	char  *line = NULL;
	size_t buffer_size = 0;
	ssize_t length;

	char **all_lines = NULL;
	size_t element_number = 0;
	size_t array_size = 0;

	while ((length = getline(&line, &buffer_size, f)) != -1) {
		if (element_number == array_size) {
			array_size = array_size ? array_size * 2 : 16;
			char **new_space = realloc(all_lines, array_size * sizeof(*new_space));
			if (new_space == NULL) {
				perror("Can't reallocate space!");
				for (size_t i = 0; i < element_number; i++) {
					free(all_lines[i]);
				}
				free(all_lines);
				free(line);
				exit(EXIT_FAILURE);
			}
			all_lines = new_space;
		}
		all_lines[element_number++] = line;
		line = NULL;
		buffer_size = 0;
	}

	if (ferror(f)) {
		perror("Reading file error");
		for (size_t i = 0; i < element_number; i++) {
			free(all_lines[i]);
		}
		free(all_lines);
		free(line);
		exit(EXIT_FAILURE);
	}
	
	sortData(all_lines, element_number);

	for (size_t i = 0; i < element_number; i++) {
		printf("%s", all_lines[i]);
		free(all_lines[i]);
	}
	free(all_lines);
	free(line);
}	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
	FILE * f = fopen(filename, "r");
	counts_t * counts = createCounts();
	if (f == NULL) {
		perror("Could not open file!\n");
		return counts;
	}
	char * line = NULL;
	size_t size = 0;
	while (getline(&line, &size, f) >= 0) {
		char * p = strchr(line, '\n');
		if (p != NULL) {
			*p = '\0';
		}

		char * value = lookupValue(kvPairs, line);
		addCount(counts, value);
	}
	free(line);
	if (fclose(f) != 0) {
		perror("Cannt close file!\n");
	}
	return counts;	
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
	if (argc < 3) {
		fprintf(stderr, "argument number wrong!\n");
		return EXIT_FAILURE;
	}
	
	kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c
	for (int i = 2; i < argc; i++) {
		counts_t * c = countFile(argv[i], kv);
		char * out_file_name = computeOutputFileName(argv[i]);

		FILE * f = fopen(out_file_name, "w");
		if (f == NULL) {
			perror("Cannot open file!\n");
			free(out_file_name);
			freeCounts(c);
			freeKVs(kv);
			return EXIT_FAILURE;
		}
		printCounts(c, f);
		if (fclose(f) != 0) {
			perror("cannt close file!\n");
			free(out_file_name);
			freeCounts(c);
			freeKVs(kv);	
			return EXIT_FAILURE;	
		}


 //free the memory for kv
		free(out_file_name);
		freeCounts(c);
	}
	freeKVs(kv);	

	return EXIT_SUCCESS;
}

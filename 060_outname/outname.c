#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
	if (inputName == NULL) {
		return NULL;
	}

	size_t space_needed = strlen(inputName) + sizeof(".counts");
	char *determined_name = malloc(space_needed);
	if (determined_name == NULL) {
		perror("malloc problems!");
		return NULL;
	}
	strcpy(determined_name, inputName);
	strcat(determined_name, ".counts");
	return determined_name;	
}

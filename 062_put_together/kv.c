#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
	FILE *f = fopen(fname, "r");
	if (f == NULL) {
		perror("fopen problems");
	       	return NULL; 
	}

	kvarray_t *data = malloc(sizeof(*data));
	if(data == NULL) {
		perror("malloc problems");	
		fclose(f);
		return NULL;
	}	
	data->pairs = NULL;
	data->length = 0;

	size_t capacitance = 0;
	char *line = NULL;
	size_t current_line_buffer = 0;
	ssize_t num_read;

	while ((num_read = getline(&line, &current_line_buffer, f)) >= 0) {
		if (num_read > 0 && (line[num_read - 1] == '\n')) {
			line[--num_read] = '\0';
		}
		if (line[0] == '\0') {
			continue;
		}

		char *equal = strchr(line, '=');
		if (equal == NULL) {
			continue;
		}
		*equal = '\0';
		char *key = line;	
		char *value = equal + 1;
	
		if (data->length == capacitance) {
			size_t new_capacitance = capacitance ? capacitance* 2 :32;
			kvpair_t *new_space = realloc(data->pairs, new_capacitance* sizeof(*new_space));
			if (new_space == NULL) {
				perror("realloc problems");	
				free(line);
				fclose(f);
			
				for (size_t i = 0; i < data->length; i++) {
					free(data->pairs);	
					free(data);
					return NULL;
				}
			}	
			data->pairs = new_space;
			capacitance = new_capacitance;
		}	

		kvpair_t *to_be_saved = &data->pairs[data->length++];
		to_be_saved->key = strdup(key);
		to_be_saved->value = strdup(value);

		if (to_be_saved->key == NULL|| to_be_saved->value == NULL) {
			perror("somoething wrong");
		}
	}
	free(line);
	if (fclose(f) != 0) perror("cannot close");	
	return data;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
	if (pairs == NULL) {
		return;
	}
	for (size_t i = 0; i < pairs->length; i++) {
		free(pairs->pairs[i].key);
		free(pairs->pairs[i].value);
	}
	free(pairs->pairs);
	free(pairs);	
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
	if (pairs == NULL) {
		return;
	}
	for (size_t i = 0; i < pairs->length; i++) {
		printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
	}	
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
	if (pairs == NULL || key == NULL) {
		return NULL;
	}
	for (size_t i = 0; i < pairs->length; i++) {
		if (strcmp(pairs->pairs[i].key, key) == 0) {
			return pairs->pairs[i].value;
		}
	}
	return NULL;	
}

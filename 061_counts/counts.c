#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
	counts_t * count = malloc(sizeof(*count));
	count->array = NULL;
	count->size = 0;
	count->unknown = 0;
	return count;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
	if (name == NULL) {
		c->unknown++;
		return;
	}
	for (size_t i = 0; i < c->size; i++) {
		if (strcmp(c->array[i]->string, name) == 0) {
			c->array[i]->count++;
			return;
		}
	}
	one_count_t **tmp = realloc(c->array, (c->size + 1) * sizeof(*c->array));
	c->array = tmp;

	one_count_t * new_count = malloc(sizeof(*new_count));
	new_count->string = strdup(name);
	new_count->count = 1;

	c->array[c->size] = new_count;
	c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
	if (c == NULL || outFile == NULL) {
		return;
	}
	for (size_t i = 0; i < c->size; i++) {
		fprintf(outFile, "%s: %d\n", c->array[i]->string, c->array[i]->count);
	}
	if (c->unknown > 0) {
		fprintf(outFile, "<unknown> : %d\n", c->unknown);
	}
}

void freeCounts(counts_t * c) {
  //WRITE ME
	for (size_t i = 0; i < c->size; i++) {
		free(c->array[i]->string);
		free(c->array[i]);
	}
	free(c->array);
	free(c);
}

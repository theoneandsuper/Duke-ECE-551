#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>

//any functions you want your main to use
void process_story_file (FILE * f);
void parse_category_file (FILE * f, catarray_t * category_list);
void free_category_list(catarray_t * category_list);

typedef struct used_word_list_tag {
	char ** words;
	size_t n_words;
} used_word_list_t;

void process_single_line_step3(const char * line, catarray_t * categroty_list, used_word_list_t * used_word_list);
void process_single_line_step4(const char * line, catarray_t * categroty_list, used_word_list_t * used_word_list, int if_can_be_reused);
int story_process_main(const char *words_file, const char *story_file, int if_can_be_reused);
#endif

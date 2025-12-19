#include "rand_story.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>

void process_single_line(const char * line);

int parse_category_line(const char * line, catarray_t * category_list);

char * malloc_string_copy(const char * start, size_t size);

int handle_new_category_or_word(catarray_t * category_list, char * category, char * word);

ssize_t find_category_index(const catarray_t *category_list, const char *category_name);

void free_category_list(catarray_t * category_list);

long parse_positive_number_string(const char * string);

const char * get_referenced_word(const used_word_list_t * used_word_list, long back_index);

void add_used_word(used_word_list_t * used_word_list, const char * used_word);

void remove_word_from_category(catarray_t * category_list, const char * category_name, const char * word_to_be_removed);

void process_story_file (FILE * f) {
	char * line = NULL;
	size_t buffer_size = 0;
	while (getline(&line, &buffer_size, f) >= 0) {
		process_single_line(line);
	}
	free(line);
}

void process_single_line (const char * line) {
	//I think I would better have local one, may need to print the line
	const char * line_pointer = line;
	//not the end
	while (*line_pointer != '\0') {
		if (*line_pointer == '_') {
			line_pointer++;
			//the noun found
			const char * word_start = line_pointer;
			while (*line_pointer != '_' && *line_pointer != '\0') {
				line_pointer++;
			}	
			//checking the # of _ should have another one before end
			if (*line_pointer == '\0') {
				fprintf(stderr, "_ must be in pairs!\n");
				exit(EXIT_FAILURE);
			}

			//pointer not countint more if _
			size_t word_length = line_pointer - word_start;
			char * extracted_word = strndup(word_start, word_length);
			const char * to_be_printed = chooseWord(extracted_word, NULL);
			printf("%s", to_be_printed);
			line_pointer++;
			//free the space at last
			free(extracted_word);
		}
		else {
			//we just keep whatever it looks like
			putchar(*line_pointer);
			line_pointer++;
		}
	}
}		

void parse_category_file (FILE * f, catarray_t * category_list) {
	//First inititalize it
	category_list->arr = NULL;
	category_list->n = 0;

	//just again the classical getline part
	char * line = NULL;
	size_t buffer_size = 0;
	
	while (getline(&line, &buffer_size, f) >= 0) {
		//check if just \n, if full just free line later
		if (strcmp(line, "\n") == 0) {	
			fprintf(stderr, "At least one line contains nothing!\n");
			free(line);
			exit(EXIT_FAILURE);
		}

		if (parse_category_line(line, category_list) == -1) {
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	//at last free line
	free(line);

}

int parse_category_line(const char * line, catarray_t * category_list) {
	//no : is false, : at 1st is not correct
	const char * colon_position = strchr(line, ':');
	if (colon_position == NULL || colon_position == line) {
		fprintf(stderr, ": number or position is wrong!\n");
		return -1;
	}
	
	//copy category name
	size_t category_length = (size_t)(colon_position - line);
	char * category_name = malloc_string_copy(line, category_length);
	
	//to copy word
	const char * word_start = colon_position + 1;
	int word_length = 0;

	while (word_start[word_length] != '\0' && word_start[word_length] != '\n') {
		word_length++;
	}
	
	//let -1 be error
	if (word_length == 0) {
		fprintf(stderr, "the word cannot have null!\n");
		free(category_name);
		return -1;
	}

	char * word_content = malloc_string_copy(word_start, word_length);
	
	return handle_new_category_or_word(category_list, category_name, word_content);


}

char * malloc_string_copy(const char * start, size_t size) {
	char * malloc_string = malloc(size + 1);
	memcpy(malloc_string, start, size);
	//null terminated at last
	malloc_string[size] = '\0';
	return malloc_string;
}

int handle_new_category_or_word(catarray_t * category_list, char * category_name, char * word) {
	//look for the category
	ssize_t if_category_exist = find_category_index(category_list, category_name);
	
	if (if_category_exist == -2) {
		//new space to add the new category
		category_t * new_category_list = realloc(category_list->arr, (category_list->n + 1) * sizeof(*new_category_list));
		category_list->arr = new_category_list;
		size_t new_index = category_list->n;
		
		//fill up new category
		category_list->arr[new_index].name = category_name;
		category_list->arr[new_index].n_words = 0;
		category_list->arr[new_index].words = NULL;

		//setup word
		category_list->arr[new_index].words = malloc(sizeof(*category_list->arr[new_index].words));
		category_list->arr[new_index].words[0] = word;
		category_list->arr[new_index].n_words = 1;

		category_list->n++;
		return (int)new_index;
	}
	else {
		//write on existing one
		category_t * existing_category = &category_list->arr[if_category_exist];
		char ** new_words = realloc(existing_category->words, (existing_category->n_words + 1) * sizeof(*new_words));

		existing_category->words = new_words;
		existing_category->words[existing_category->n_words] = word;
		existing_category->n_words++;

		//free at last
		free(category_name);
		return (int)if_category_exist;
	}
}

ssize_t find_category_index(const catarray_t *category_list, const char *category_name) {
	for (size_t i = 0; i < category_list->n; i++) {
		if (strcmp(category_list->arr[i].name, category_name) == 0) {
			return (ssize_t)i;
		}
	}
	return -2;
}

void free_category_list(catarray_t * category_list) {
	if (category_list== NULL) {
		return;
	}
	for (size_t i = 0; i < category_list->n; i++) {
		//free very single word
		for (size_t j = 0; j < category_list->arr[i].n_words; j++) {
			free(category_list->arr[i].words[j]);
		}
		free(category_list->arr[i].words);

		//free category names
		free(category_list->arr[i].name);
	}

	free(category_list->arr);
	category_list->arr = NULL;
	category_list->n = 0;
}

void process_single_line_step3(const char * line, catarray_t * categroty_list, used_word_list_t * used_word_list) {
	//similarly definre a local pointer first (will just copy and paste previous)
	const char * line_pointer = line;
	//not the end of string
	while (*line_pointer != '\0') {
		if (*line_pointer == '_') {
			line_pointer++;
			const char * word_start = line_pointer;
			while (*line_pointer != '_' && *line_pointer != '\0') {
				line_pointer++;
			}
			//checking the # of _ should have another one before end
			if (*line_pointer == '\0') {
				fprintf(stderr, "_ must be in pairs!\n");
				exit(EXIT_FAILURE);
			}

			size_t word_length = line_pointer - word_start;
			char * extracted_word = strndup(word_start, word_length);

			//now add new functionality to retrieve the number
			const char * chosen_word = NULL;
			long retrieved_number = parse_positive_number_string(extracted_word);
			if (retrieved_number != -1) {
				chosen_word = get_referenced_word(used_word_list, retrieved_number);
			}
			else {
				//could then try if it is a category name, it will generate failure itself if not
				chosen_word = chooseWord(extracted_word, categroty_list);
			}
			
			//add this to used_word_list before moving
			add_used_word(used_word_list, chosen_word);
			//same logic in process_single_line
			printf("%s", chosen_word);
			line_pointer++;
			free(extracted_word);
		}
		else {
			putchar(*line_pointer);
			line_pointer++;
		}
	}
}

long parse_positive_number_string(const char * string) {
	char * stopped_place;
	//use base 10 so that 1.3x could be detected
	long number = strtol(string, &stopped_place, 10);
	
	if (string == stopped_place) {
		//not number start
		return -1;
	}
	if (*stopped_place!= '\0') {
	//contain 123abc not all numbers, invalid
		return -1;
	}
	if (number < 1) {
		return -1;
	}
	return number;
}

const char * get_referenced_word(const used_word_list_t * used_word_list, long back_index) {
	if ((size_t)back_index > used_word_list->n_words) {
		//exceeding the limit
		fprintf(stderr, "referencing outside the range\n");
		exit(EXIT_FAILURE);
	}
	return used_word_list->words[(size_t)(used_word_list->n_words - back_index)];
}

void add_used_word(used_word_list_t * used_word_list, const char * used_word) {
	//copied from handle_new_category_part, same logic
	char **new_used_word_list = realloc(used_word_list->words, (used_word_list->n_words + 1) * sizeof(*used_word_list->words));
	used_word_list->words = new_used_word_list;
	used_word_list->words[used_word_list->n_words] = strdup(used_word);
	used_word_list->n_words++;
}

void process_single_line_step4(const char * line, catarray_t * categroty_list, used_word_list_t * used_word_list, int if_can_be_reused) {
	//the whole function will be a copy and paste of step3
	const char * line_pointer = line;
	while (*line_pointer != '\0') {
		if (*line_pointer == '_') {
			line_pointer++;
			const char * word_start = line_pointer;
			while (*line_pointer != '_' && *line_pointer != '\0') {
				line_pointer++;
			}
			if (*line_pointer == '\0') {
				fprintf(stderr, "_ must be in pairs!\n");
				exit(EXIT_FAILURE);
			}

			size_t word_length = line_pointer - word_start;
			char * extracted_word = strndup(word_start, word_length);

			const char * chosen_word = NULL;
			long retrieved_number = parse_positive_number_string(extracted_word);
			if (retrieved_number != -1) {
				chosen_word = get_referenced_word(used_word_list, retrieved_number);
				add_used_word(used_word_list, chosen_word);
			}
			else {
				chosen_word = chooseWord(extracted_word, categroty_list);
				//starts to have difference
				add_used_word(used_word_list, chosen_word);
				//this is the only line different fron step3, after chosing it, remove it
				printf("%s", chosen_word);
				if (if_can_be_reused == 0) {
					remove_word_from_category(categroty_list, extracted_word, chosen_word);
				}
			}
			if (retrieved_number != -1) {
				printf("%s", chosen_word);
			}
			//the rest should be the same
			line_pointer++;
			free(extracted_word);
		}
		else {
			putchar(*line_pointer);
			line_pointer++;
		}
	}
}

void remove_word_from_category(catarray_t * category_list, const char * category_name, const char * word_to_be_removed) {
	ssize_t category_index = find_category_index(category_list, category_name);
	
	if (category_index == -2) {
		fprintf(stderr, "you just modified your file!?\n");
		exit(EXIT_FAILURE);
	}

	category_t * target_category = &category_list->arr[category_index];

	//look for the specific word, similar logic with look for category, but it uses n_word
	ssize_t word_index = -2;
	for (size_t i = 0; i < target_category->n_words; i++) {
		if (strcmp(target_category->words[i], word_to_be_removed) == 0) {
			word_index = (ssize_t)i;
			break;
		}
	}
	if (word_index == -2) {
	       //actually it should not happen cause we just found it
	       fprintf(stderr, "you just modified your file!?\n");
	       exit(EXIT_FAILURE);	 
	}

	//swap with last to remove
	size_t last_index = target_category->n_words - 1;
	free(target_category->words[word_index]);
	if (word_index != last_index) {
		target_category->words[word_index] = target_category->words[last_index];
	}
	target_category->n_words--;
		
	//then we resize according to the new adjusted size
	if (target_category->n_words == 0) {
		free(target_category->words);
		target_category->words = NULL;
	}
	else {
		//just realloc
		char ** resized_category_list = realloc(target_category->words, target_category->n_words * sizeof (*target_category->words));
		target_category->words = resized_category_list;
	}
}	


int story_process_main(const char *words_file, const char *story_file, int if_can_be_reused) {
	//this is the method I came up with to try to fulfill the reuse requirement for grading and to reduce work
	//first deal with word file
	FILE *f_words = fopen(words_file, "r");
	if (f_words == NULL) {
		perror("check if word_file exist");
		return EXIT_FAILURE;
	}

	catarray_t category_list;
	parse_category_file(f_words, &category_list);
	fclose(f_words);

	//initialize used_word_list
	used_word_list_t used_word_list;
	used_word_list.words = NULL;
	used_word_list.n_words = 0;

	//deal with story file
	FILE *f_story = fopen(story_file, "r");
	if (f_story == NULL) {
		perror("check if story_file exists!");
		free_category_list(&category_list);
		return EXIT_FAILURE;
	}

	//classical getline part
	char *line = NULL;
	size_t buffer_size = 0;
	while (getline(&line, &buffer_size, f_story) >= 0) {
		if (if_can_be_reused == 1) {
			process_single_line_step3(line, &category_list, &used_word_list);
		}
		else {
			process_single_line_step4(line, &category_list, &used_word_list, if_can_be_reused);
		}
	}

	//free
	free(line);
	fclose(f_story);
	for (size_t i = 0; i < used_word_list.n_words; i++) {
		free(used_word_list.words[i]);
	}
	free(used_word_list.words);
	free_category_list(&category_list);

	return EXIT_SUCCESS;
}

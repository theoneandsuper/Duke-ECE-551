#include "myinput.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

bool all_digits_check(const char *array);

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
	//check if inputs right
	if (planet == NULL || line == NULL) {
		fprintf(stderr, "At least one of the inputs is NULL!\n");
		exit(EXIT_FAILURE);
	}

	char safe_copy[128];
	strncpy(safe_copy, line, sizeof(safe_copy));
	safe_copy[sizeof(safe_copy) - 1] = '\0';

	//if reading whole file line by line, remove \n
	safe_copy[strcspn(safe_copy, "\n")] = '\0';

	//basic format check (3:, 0\n, 1\0)
	int colon_counter = 0;
	int new_line_counter = 0;
	int null_counter = 0; 
	for (const char *p = safe_copy; ; p++) {
		unsigned char name_char_checked = (unsigned char)*p;

		if (name_char_checked == ':') {
			colon_counter++;
		}
		else if (name_char_checked == '\n') {
			new_line_counter++;
		}
		else if (name_char_checked == '\0') {
			null_counter++;
			break;
		}
	}
	if (colon_counter != 3 || new_line_counter != 0 || null_counter != 1) {
		fprintf(stderr, "Might be name wrong!\n");
		exit(EXIT_FAILURE);
	}
	
	//name
	char *part1_end  = strchr(safe_copy, ':');
	if (part1_end == NULL) {
		fprintf(stderr, "Format error, 0 number of :\n");
		exit(EXIT_FAILURE);
	}
	size_t name_length = strcspn(safe_copy, ":");
	if (name_length >= MAX_PLANET_NAME_LEN) {
		fprintf(stderr, "Planet name too long!\n");
		exit(EXIT_FAILURE);
	}

	//I have to do a same name checking!
	//char name_checking_buffer[name_length + 1];
	//memcpy(name_checking_buffer, safe_copy, name_length);	
	memcpy(planet->name, safe_copy, name_length);
	planet->name[name_length] = '\0';

	//orbital_radius
	char *part2_start = part1_end + 1;
	char *part2_end = strchr(part2_start, ':');
	size_t radius_length = part2_end - part2_start;
	char temp_p2[radius_length + 1];
	memcpy(temp_p2, part2_start, radius_length);
	temp_p2[radius_length] = '\0';
	if (all_digits_check(temp_p2) == false) {
		fprintf(stderr, "Orbital_radius input form incorrent!\n");
        	exit(EXIT_FAILURE);
	}		
	planet->orbital_radius = strtod(temp_p2, NULL);
	if (planet->orbital_radius <= 0.0) {
		fprintf(stderr, "Orbital_raius cann't be less than zero!\n");
		exit(EXIT_FAILURE);
	}	
	
	//year_len
	char *part3_start = part2_end + 1;
	char *part3_end = strchr(part3_start, ':');
	size_t year_length = part3_end - part3_start;
	char temp_p3[year_length + 1];
	memcpy(temp_p3, part3_start, year_length);
	temp_p3[year_length] = '\0';
	if (all_digits_check(temp_p3) == false) {
		fprintf(stderr, "Year_len input incorrent!\n");
		exit(EXIT_FAILURE);
	}
	double input_year_length = strtod(temp_p3, NULL);
	if (input_year_length <= 0.0) {
		fprintf(stderr, "Year_len must be positive!\n");
		exit(EXIT_FAILURE);
	}	
	planet->year_len = input_year_length;	

	//init_pos
	char *part4_start = part3_end + 1;
	char *part4_end = safe_copy + sizeof(safe_copy) - 1;
	size_t init_pos = part4_end - part4_start;
	char temp_p4[init_pos + 1];
	memcpy(temp_p4, part4_start, init_pos);
	temp_p4[init_pos] = '\0';
	if (all_digits_check(temp_p4) == false) {
		fprintf(stderr, "Init_pos input incorrent!\n");
		exit(EXIT_FAILURE);
	}	
	planet->init_pos = strtod(temp_p4, NULL);
	planet->init_pos = planet->init_pos * M_PI / 180.0;
	
}

bool all_digits_check(const char * array) {
	if (array == NULL || array[0] == '\0') {
		return false;
	}

	for (int i = 0; array[i] !='\0'; i++) {
		if (!isdigit((unsigned char)array[i])) {
			return false;	
		}
	}
	return true;
}	

#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"
#include <math.h>

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
	point_t cordinate;
	double angle = fmod(p->init_pos + 2 * M_PI * time / p->year_len, 2 * M_PI);
	cordinate.x = p->orbital_radius * cos(angle);
	cordinate.y = p->orbital_radius * sin(angle);
        return cordinate;	
}

planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
	if (lst == NULL || name == NULL) {
		fprintf(stderr, "At least one of the inputs is NULL!\n"); 
		exit(EXIT_FAILURE);
	}
	
	int same_name_counter = 0;
	for (size_t i = 0; i < lst->num_planets; i++) {
		planet_t *p = lst->planets[i];
		planet_t *to_be_returned;
		if (same_name_counter == 0 && p != NULL && strcmp(p->name, name) == 0) {
			same_name_counter++;
			to_be_returned = lst->planets[i];
		}
		//else if (same_name_counter == 1 && strcmp(p->name, name) == 0) {
		//	if (p->orbital_radius != to_be_returned->orbital_radius || p->year_len != to_be_returned->year_len || p->init_pos != to_be_returned->init_pos) {
			//	fprintf(stderr, "Make sure information matches!");
			//	exit(EXIT_FAILURE);
		//	}
	//	}
		if (i == lst->num_planets - 1 && same_name_counter == 1) {
			return to_be_returned;
		}
	}

	fprintf(stderr, "Planet name not found!\n");
	exit(EXIT_FAILURE);
}

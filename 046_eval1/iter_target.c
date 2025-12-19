#include "iter_target.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "planet_util.h"

double distance(point_t a, point_t b);

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
	//basic checking
	if (this_launch == NULL || planets == NULL) {
		fprintf(stderr, "At least one of the inputs is NULL!\n");
		exit(EXIT_FAILURE);
	}

	//basic information gathering
	planet_t *source_planet = find_planet(planets, this_launch->src);
	planet_t *destination_planet = find_planet(planets, this_launch->dest);
	double speed = this_launch->speed;
	double close_distance = this_launch->close_enough;
	double launch_time = this_launch->time;
	point_t source_location = get_location_at(source_planet, launch_time);
	point_t destination_location = get_location_at(destination_planet, launch_time);
	double time_might_takes = distance(source_location, destination_location) / speed; 
	double destination_period = destination_planet->year_len;
	double best_flight_time = DBL_MAX;
	double best_total_time = DBL_MAX;
	launch_result_t best_launch_result;

	if (speed == 0.0) {
		best_launch_result.theta = 0;
		best_launch_result.duration = INFINITY;
		return best_launch_result;
	}
	
	if (distance(source_location, destination_location) == 0.0) {
		best_launch_result.theta = -NAN;
		best_launch_result.duration = 0.0;
		return best_launch_result;
	}

	for (uint64_t i = 0; i < this_launch->max_iterations; i++) {
		point_t target_destination;
		if (i == 0) {
			target_destination = destination_location;
		}
		else {	
			target_destination = get_location_at(destination_planet, launch_time + time_might_takes);
		}	
		double time_takes = distance(source_location, target_destination) / speed;	
       		//real_destination_location at that time		
		if (distance(get_location_at(destination_planet, launch_time + time_takes), target_destination) <= close_distance) {
			best_total_time = time_takes;
			double angle_traveling = atan2(target_destination.y - source_location.y, target_destination.x -  source_location.x);
			if (angle_traveling < 0.0) {
				angle_traveling += 2 * M_PI;
			}
			best_launch_result.theta = angle_traveling;
		       	best_launch_result.duration = best_total_time;
			return best_launch_result;
		}
		
		double time_diff = time_might_takes - time_takes;
		double wait_time = fmod(time_diff, destination_period);
		if (wait_time < 0.0) {
			wait_time += destination_period;
		}
		double total_time = time_takes + wait_time;
		if (total_time < best_total_time) {
			best_total_time  = total_time;
			double angle_traveling = atan2(target_destination.y - source_location.y, target_destination.x -  source_location.x);
			if (angle_traveling < 0.0) {
				angle_traveling += 2 * M_PI;
			}
			best_launch_result.theta = angle_traveling;	
			best_flight_time = time_takes;
		} 	

		time_might_takes = time_takes;
	}
	
	best_launch_result.duration = best_flight_time;
	return best_launch_result;	
}		

double distance(point_t a, point_t b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}	

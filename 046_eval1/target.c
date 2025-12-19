#include "target.h"
#include <math.h>
#include "planet_util.h"

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
	//basic infor gathered
	double current_launch = this_launch->time;
	planet_t *source_planet = find_planet(planets, this_launch->src);
	planet_t *destination_planet = find_planet(planets, this_launch->dest);

	point_t current_source_location = get_location_at(source_planet, current_launch);
	point_t current_destination_location = get_location_at(destination_planet, current_launch);

	double x_distance = current_destination_location.x - current_source_location.x;
	double y_distance = current_destination_location.y - current_source_location.y;	
	
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);

	launch_result_t to_be_returned;
	//checking 0,0 itself case
	if (distance == 0.0) {
		to_be_returned.theta = -NAN;
		to_be_returned.duration = 0.0;
		return to_be_returned;
	}	

	double angle = atan2(y_distance, x_distance);
	while (angle < 0.0) {
		angle += M_PI * 2;
	}
	double time_takes = distance / this_launch->speed;

	//returned calculation
	to_be_returned.theta = angle;
	to_be_returned.duration = time_takes;
	return to_be_returned;	
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
	double angle_of_target = atan2(pos.y, pos.x);
	double angular_velocity = 2 * M_PI / planet->year_len;
	double current_angle = fmod(planet->init_pos + angular_velocity * start_time, 2.0 * M_PI);
	double angular_diff = angle_of_target - current_angle;
	while  (angular_diff < 0.0) {
		angular_diff += M_PI * 2;
	}
	
	return start_time + angular_diff / angular_velocity;
}

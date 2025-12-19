#include <iostream>
#include <cstdlib>
#include <climits>
#include "tanker_ship.hpp"

TankerShip::TankerShip(const std::string & name, const std::string & source, const std::string & destination, uint64_t total_capacity, int min_temperature, int max_temperature, 
		       unsigned int num_tanks, const std::set<std::string> & hazard_capabilities) : 
		       Ship(name, source, destination, total_capacity, 0, hazard_capabilities), min_temperature(min_temperature), max_temperature(max_temperature), 
		       num_tanks(num_tanks), per_tank_capacity(0), tanks() {//just slot is not needed for tankship
	if (num_tanks == 0) { 
		std::cerr << "Your tank ship has no tank at all!\n";
		std::exit(EXIT_FAILURE);
	}
	//as required must be dividible
	if (total_capacity % num_tanks != 0) {
		std::cerr << "Your tanker ship capacity is divisible!\n";
		std::exit(EXIT_FAILURE);
	}
	//reassign the ptc value
	per_tank_capacity = total_capacity / num_tanks;
	//resize tanks vecotor size
	tanks.resize(num_tanks);
}

void TankerShip::change_temperature(int & extreme_cargo_temperature, const std::string & key, const std::vector<std::string> & properties) const {
	for (const std::string & property : properties) {
		//deal with one extreme temp, just mintemp or maxtemp
		if (property == key) {
			extreme_cargo_temperature = 0;
		}

		//extremetemp= 
		else if (property.rfind(key + "=", 0) == 0) {
			//take the rest as value
			std::string value = property.substr(key.size() + 1);
			//if value is empty
			if (value.empty()) {
				//not shoudld be 0 or intmin?
				return;
			}
			//conver to cstring to use the classical strtol
			const char * cstring_value = value.c_str();
			char * end_pointer = NULL;
			long final_value = std::strtol(cstring_value, &end_pointer, 10);
			//if no digit at all or contains non digit later
			if (end_pointer == cstring_value || *end_pointer != '\0') {
				std::cerr << "Invalid " << key << "!\n";
				std::exit(EXIT_FAILURE);
			}
			//final adjustment of value
			if (final_value > INT_MAX) final_value = INT_MAX;
			if (final_value < INT_MIN) final_value = INT_MIN;

			extreme_cargo_temperature = static_cast<int>(final_value);
		}
	}
}

void TankerShip::form_cargo_temperature_requirements(const Cargo & cargo, int & cargo_temperature_min, int & cargo_temperature_max) const {
	//by default we assumes no requirements by giving extreme values
	cargo_temperature_min = INT_MIN;
	cargo_temperature_max = INT_MAX;

	//get all the properties
	const std::vector<std::string> & properties = cargo.get_properties();

	//call the function just written twice to actually form caro temp requirem
	change_temperature(cargo_temperature_min, "mintemp", properties);
	change_temperature(cargo_temperature_max, "maxtemp", properties);
}

bool TankerShip::if_temperature_ok(const Cargo & cargo) const {
	//I think I dont need to initialize them
	int assumed_cargo_mint;
	int assumed_cargo_maxt;
	form_cargo_temperature_requirements(cargo, assumed_cargo_mint, assumed_cargo_maxt);
	return (get_max_temperature() >= assumed_cargo_mint) && (assumed_cargo_maxt >= get_min_temperature());
}	

void TankerShip::fill_tanks_for_cargo(std::vector<Tank> & tanks_list, uint64_t & weight_to_handle, const std::string & cargo_name) const {
	//simulating filling same name cargo tank
	for (std::size_t i = 0; i < tanks_list.size() && weight_to_handle > 0; i++) {
		if (!tanks_list[i].cargo_name.empty() && tanks_list[i].cargo_name == cargo_name) {
			uint64_t used_in_this_tank = tanks_list[i].used_capacity;
			if (used_in_this_tank < get_per_tank_capacity()) {
				uint64_t available_in_tank = get_per_tank_capacity() - used_in_this_tank;
				uint64_t this_taken = (available_in_tank < weight_to_handle) ? available_in_tank : weight_to_handle;
				tanks_list[i].used_capacity += this_taken;
				weight_to_handle -= this_taken;
			}
		}
	}

	//now use new empty tanks
	for (std::size_t i = 0; i < tanks_list.size() && weight_to_handle > 0; i++) {
		//not used at all
		if (tanks_list[i].used_capacity == 0) {
			tanks_list[i].cargo_name = cargo_name;
			uint64_t this_taken = (get_per_tank_capacity() < weight_to_handle) ? get_per_tank_capacity() : weight_to_handle;
			tanks_list[i].used_capacity = this_taken;
			weight_to_handle -= this_taken;
		}
	}
}

bool TankerShip::if_tank_size_ok(const Cargo & cargo) const {
	uint64_t weight_to_handle = cargo.get_weight();
	const std::string & cargo_name = cargo.get_name();

	//create a new copy to try to solve the cargo problem
	std::vector<Tank> tanks_copy = tanks;
	fill_tanks_for_cargo(tanks_copy, weight_to_handle, cargo_name);
	//at last we see if there are remainings of the this cargro to handle
	if (weight_to_handle == 0) {
		return true;
	}
	return false;
}

bool TankerShip::if_could_carry(const Cargo & cargo) const {
	//same route check
	if (cargo.get_source() != get_source() || cargo.get_destination() != get_destination()) {
		return false;
	}

	//hazard check
	std::vector<std::string> hazard_requirements = cargo.extract_hazard_requirements();
	for (std::size_t i = 0; i < hazard_requirements.size(); i++) {
		if (hazard_capabilities.count(hazard_requirements[i]) == 0) {
			return false;
		}
	}

	//weight check
	if (get_total_capacity() < get_used_capacity() + cargo.get_weight()) {
		return false;
	}

	//liquid gas check (opposite from animal)
	if (!(cargo.if_has_property("liquid") || cargo.if_has_property("gas"))) {
		return false;
	}
	
	//the two special specific checks
	if (!if_temperature_ok(cargo)) {
		return false;
	}

	if (!if_tank_size_ok(cargo)) {
		return false;
	}

	return true;
}

void TankerShip::load_in_tanks(const Cargo & cargo) {
	uint64_t weight_to_handle = cargo.get_weight();
	const std::string & cargo_name = cargo.get_name();

	fill_tanks_for_cargo(tanks, weight_to_handle, cargo_name);

	//and it should be zero now if my if_could_carry logic is right
}

void TankerShip::load(const Cargo & cargo) {
	//the users must check if could load first then use this method
	load_in_tanks(cargo);

	used_capacity += cargo.get_weight();
	loaded_cargo.push_back(cargo);
}

void TankerShip::print_status() const {
	std::cout << "The Tanker Ship " << get_name() << "(" << get_used_capacity() << "/" << get_total_capacity() << ") is carrying :\n";

	//print out all the cargos
	for (std::size_t i = 0; i < loaded_cargo.size(); i++) {
		const Cargo & cargo = loaded_cargo[i];
		std::cout << "  " << cargo.get_name() << "(" << cargo.get_weight() << ")\n";
	}

	//return the num of tanks used
	unsigned int num_used_tanks = 0;
	for (std::size_t i = 0; i < tanks.size(); i++) {
		if (tanks[i].used_capacity > 0) {
			num_used_tanks++;
		}
	}

	std::cout << "  " << num_used_tanks << " / " << num_tanks << " tanks used\n";
}

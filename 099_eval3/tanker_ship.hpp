#ifndef TANKER_SHIP_HPP
#define TANKER_SHIP_HPP

#include <vector>
#include "ship.hpp"

class TankerShip : public Ship {
	int min_temperature;
	int max_temperature;
	unsigned int num_tanks;
	uint64_t per_tank_capacity;
	//note a new field tank is required to record extra info, I decide to make it a struct
	struct Tank {
		std::string cargo_name;
		uint64_t used_capacity;
		Tank() : cargo_name(), used_capacity(0) {}
	};
	std::vector<Tank> tanks;
	
	void change_temperature(int & extreme_cargo_temperature, const std::string & key, const std::vector<std::string> & properties) const;

	void form_cargo_temperature_requirements(const Cargo & cargo, int & cargo_temperature_min, int & cargo_temperature_max) const;

	//after careful consideration, I think making the two conditions seperately is easier to write
	bool if_temperature_ok(const Cargo & cargo) const;
	
	void fill_tanks_for_cargo(std::vector<Tank> & tanks_list, uint64_t & weight_to_handle, const std::string & cargo_name) const;

	bool if_tank_size_ok(const Cargo & cargo) const;

	void load_in_tanks(const Cargo & cargo);

	public:
		TankerShip(const std::string & name, const std::string & source, const std::string & destination, uint64_t total_capacity, int min_temperature, 
			   int max_temperature, unsigned int num_tanks, const std::set<std::string> & hazard_capabilities);

		int get_min_temperature() const {
			return min_temperature;
		}

		int get_max_temperature() const {
			return max_temperature;
		}

		unsigned int get_num_tanks() const {
			return num_tanks;
		}

		uint64_t get_per_tank_capacity() const {
			return per_tank_capacity;
		}
		
		virtual bool if_could_carry(const Cargo & c) const;

		virtual void load(const Cargo & c);

		virtual void print_status() const;
};

#endif

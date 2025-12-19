#include <iostream>
#include "ship.hpp"

unsigned int Ship::get_remaining_slots() const {
	//with caring careful management when adding cargos I highly doubt this if could happen but let me write it down for now
	if (total_slots <= loaded_cargo.size()) {
		return 0;
	}
	return static_cast<unsigned int>(get_total_slots() - loaded_cargo.size());
}

bool Ship::if_could_carry(const Cargo & cargo) const {
	//same route check
	if (cargo.get_source() != get_source() || cargo.get_destination() != get_destination()) {
		return false;
	}

	//ship type check
	if (!cargo.if_has_property("container")) {
		return false;
	}
	
	//weight check
	if (get_total_capacity() < get_used_capacity() + cargo.get_weight()) {
		return false;
	}

	//slot number check
	if (get_remaining_slots() == 0) {
		return false;
	}

	//hazard ability check
	std::vector<std::string> hazard_requirements = cargo.extract_hazard_requirements();
	for (std::size_t i = 0; i < hazard_requirements.size(); i++) {
		if (hazard_capabilities.count(hazard_requirements[i]) == 0) {
			return false;
		}
	}

	return true;
}

void Ship::load(const Cargo & cargo) {
	used_capacity += cargo.get_weight();
	loaded_cargo.push_back(cargo);
}

void Ship::print_status() const {
	std::cout << "The Container Ship " << get_name() << "(" << get_used_capacity() << "/" << get_total_capacity() << ") is carrying :\n";
	//a classical for loop that goes through all the cargo list
	for (std::size_t i = 0; i < loaded_cargo.size(); i++) {
		const Cargo & cargo = loaded_cargo[i];
		std::cout << "  " << cargo.get_name() << "(" << cargo.get_weight() << ")\n";
	}
	std::cout << "(" << get_remaining_slots() << ") slots remain\n";
}

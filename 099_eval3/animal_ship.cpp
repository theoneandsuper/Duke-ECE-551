#include <iostream>
#include "animal_ship.hpp"

bool AnimalShip::if_could_carry(const Cargo & cargo) const {
	//same route check
	if (cargo.get_source() != get_source() || cargo.get_destination() != get_destination()) {
		return false;
	}

	//weight check
	if (get_total_capacity() < get_used_capacity() + cargo.get_weight()) {
		return false;
	}

	//note for the animal ship, the slot check is not neccessary?
	//new checks one animal, roamer, small enough
	//first check if animal
	if (cargo.if_has_property("animal")) {
		//then check is roamer
		if (!cargo.if_has_property("roamer")) {
			//not roamer return true
			return true;
		}
		else {
			//if roamer but has no other roamer loaded
			if (!get_if_has_roamer()) {
				return true;
			}

			return false;
		}
	}
	else {
		//it is not animal
		//then it can not be liquid or gas
		if (cargo.if_has_property("liquid") || cargo.if_has_property("gas")) {
			return false;
		}

		//it can not be hazards
		std::vector<std::string> hazard_requirements = cargo.extract_hazard_requirements();
		if (!hazard_requirements.empty()) {
			return false;
		}

		//meanwhile and at last, it must be small
		if (cargo.get_weight() > get_small_enough_threshold()) {
			return false;
		}
	}
	return true;
}

void AnimalShip::load(const Cargo & cargo) {
	//no need to check since the user must use the checking method above first
	Ship::load(cargo);
	//then we check the animal roamer attribute
	if (cargo.if_has_property("animal") && cargo.if_has_property("roamer")) {
		if_has_roamer = true;
	}
}

void AnimalShip::print_status() const {
	std::cout << "The Animals Ship " << get_name() << "(" << get_used_capacity() << "/" << get_total_capacity() << ") is carrying :\n";

	//similarly we print out all the loaded cargo
	for (std::size_t i = 0; i < loaded_cargo.size(); i++) {
		const Cargo & cargo = loaded_cargo[i];	
		std::cout << "  " << cargo.get_name() << "(" << cargo.get_weight() << ")\n";
	}

	//then we print accordingly to if roamer
	if (get_if_has_roamer()) {
		std::cout << "  has a roamer\n";
	}
	else {
		std::cout << "  does not have a roamer\n";
	}
}


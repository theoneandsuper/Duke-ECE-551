#ifndef ANIMAL_SHIP_HPP
#define ANIMAL_SHIP_HPP

#include "ship.hpp"

class AnimalShip : public Ship {
	uint64_t small_enough_threshold;
	bool if_has_roamer;

	public:
		AnimalShip(const std::string & name, const std::string & source, const std::string & destination, uint64_t total_capacity, uint64_t small_enough_threshold) : 	
			   Ship(name, source, destination, total_capacity, 0, std::set<std::string>()),	
		//since Animals ship cannot have anything hazardous, the capabilities is left empty
		//now fills the two new fields
		small_enough_threshold(small_enough_threshold),
		if_has_roamer(false) {}
		
		uint64_t get_small_enough_threshold() const {
			return small_enough_threshold;
		}

		bool get_if_has_roamer() const {
			return if_has_roamer;
		}

		virtual bool if_could_carry(const Cargo & c) const;

		virtual void load(const Cargo & cargo);

		virtual void print_status() const;
};

#endif

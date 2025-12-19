#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <cstdint>
#include <set>
#include <vector>
#include "cargo.hpp"

class Ship {
	// adjusted for step 3, making them protected
	protected:
		std::string name;
		std::string source;
		std::string destination;
		uint64_t total_capacity;
		uint64_t used_capacity;
		unsigned int total_slots;
		const std::set<std::string> hazard_capabilities;
		std::vector<Cargo> loaded_cargo;

	public:
		Ship(const std::string & name, const std::string & source, const std::string & destination, uint64_t total_capacity, 
		     unsigned int total_slots, const std::set<std::string> & hazard_capabilities) : 
		     name(name), source(source), destination(destination), total_capacity(total_capacity), used_capacity(0), total_slots(total_slots), 
		     hazard_capabilities(hazard_capabilities), loaded_cargo() {}

		virtual ~Ship() {}

		const std::string & get_name() const {
			return name;
		}

		const std::string & get_source() const {
			return source;
		}

		const std::string & get_destination() const {
			return destination;
		}

		uint64_t get_total_capacity() const {
			return total_capacity;
		}

		uint64_t get_used_capacity() const {
			return used_capacity;
		}

		unsigned int get_total_slots() const {
			return total_slots;
		}

		virtual unsigned int get_remaining_slots() const;	

		virtual bool if_could_carry(const Cargo & c) const;

		virtual void load(const Cargo & c);

		virtual void print_status() const;
};

#endif


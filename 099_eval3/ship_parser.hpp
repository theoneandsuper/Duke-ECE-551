#ifndef STEP3_SHIP_PARSER_HPP
#define STEP3_SHIP_PARSER_HPP

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cstdlib>
#include "ship.hpp"
#include "tanker_ship.hpp"
#include "animal_ship.hpp"
#include "utility_functions.hpp"

class ShipParser {
	public:
		Ship * parse_line(const std::string & line) const {
			std::vector<std::string> fields = split_line(line, ':');
			if (fields.size() != 5) {
				std::cerr << "Ship Field number wrong!\n";
				std::exit(EXIT_FAILURE);
			}

			const std::string & name = fields[0];
 			const std::string & type_info = fields[1];
  			const std::string & source = fields[2];
  			const std::string & destination = fields[3];
 			uint64_t total_capacity = fix_and_return_uint64(fields[4]);

			//not need to check total_capacity because the method will check it
			if (name.empty() || source.empty() || destination.empty()) {
				std::cerr << "Some of your fields are NULL, not allowed!\n";
				std::exit(EXIT_FAILURE);
			}

			std::vector<std::string> type_info_fields = split_line(type_info, ',');
			const std::string & ship_type = type_info_fields[0];

			//container ship
			if (ship_type == "Container") {
				//containers have at least two fields
				if (type_info_fields.size() < 2) {
					std::cerr << "Your container type info doesnot have enough information!\n";
					std::exit(EXIT_FAILURE);
				}
				unsigned int total_slots = static_cast<unsigned int>(fix_and_return_uint64(type_info_fields[1]));

				std::set<std::string> hazard_capabilities;
				for (std::size_t i = 2; i < type_info_fields.size(); i++) {
					if (!type_info_fields[i].empty()) {
						hazard_capabilities.insert(type_info_fields[i]);
					}
				}

				return new Ship(name, source, destination, total_capacity, total_slots, hazard_capabilities);
			}

			//tanker
			if (ship_type == "Tanker") {
				//tanker ship fields should have at least 4
				if (type_info_fields.size() < 4) {
					std::cerr << "Your tanker type info doesnot have enough information!\n";
					std::exit(EXIT_FAILURE);
				}

				int min_temperature = std::stoi(type_info_fields[1]);
				int max_temperature = std::stoi(type_info_fields[2]);
				unsigned int num_tanks = static_cast<unsigned int>(fix_and_return_uint64(type_info_fields[3]));

				//deal with hazard
				std::set<std::string> hazard_capabilities;
				for (std::size_t i = 4; i < type_info_fields.size(); i++) {
					if (!type_info_fields[i].empty()) {
						hazard_capabilities.insert(type_info_fields[i]);
					}
				}

				return new TankerShip(name, source, destination, total_capacity, min_temperature, max_temperature, num_tanks, hazard_capabilities);
			}

			//Animal Ship
			if (ship_type == "Animals") {
				//animal ship fields should have exactly 2
				if (type_info_fields.size() != 2) {
					std::cerr << "Your animal ship info is not 2!\n";
					std::exit(EXIT_FAILURE);
				}

				uint64_t small_enough_threshold = fix_and_return_uint64(type_info_fields[1]);
				return new AnimalShip(name, source, destination, total_capacity, small_enough_threshold);
			}

			//must let me return something or it is wrong then let it be error message
			else {
				std::cerr << "Unknown ship type: " << ship_type << "\n";
				std::exit(EXIT_FAILURE);
			}
		}
};

#endif

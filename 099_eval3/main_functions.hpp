#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "ship.hpp"
#include "ship_parser.hpp"

bool load_ships_from_file(const char * file_name, ShipParser & ship_parser, std::vector<Ship *> & ships) {
	//open file and read ships
	std::ifstream ships_input(file_name);
	if (!ships_input) {
		std::cerr << "Could not open ship file!\n";
		return false;
	}
	std::string line;
	//get ships line by line
	while (std::getline(ships_input, line)) {
		if (line.empty()) {
			continue;
		}
		Ship * ship = ship_parser.parse_line(line);
		ships.push_back(ship);
	}
	return true;
}

std::ifstream read_cargo_file(const char * file_name, std::vector<Ship *> & ships) {
	//read input cargo file
        std::ifstream cargo_input(file_name);
        if (!cargo_input) {
                std::cerr << "Could not open cargo file!\n";
                //must clear before exiting
                for (std::size_t i = 0; i < ships.size(); i++) {
                        delete ships[i];
                }
                std::exit(EXIT_FAILURE);
        }
	return cargo_input;
}

void process_cargo_stream(std::istream & cargo_input, CargoParser & cargo_parser, std::vector<Ship *> & ships) {
	std::string line;
	//parse and form each cargo
	while (std::getline(cargo_input, line)) {
		if (line.empty()) {
			continue;
		}

		Cargo cargo = cargo_parser.parse_line(line);
		//then form a list of all the possible ship to ship it, let me try use pointers for efficiency
		std::vector<Ship *> capable_ships;
		for (std::size_t i = 0; i < ships.size(); i++) {
			if (ships[i]->if_could_carry(cargo)) {
				capable_ships.push_back(ships[i]);
			}
		}
		//lines too long later, and frequently used, so I decide to name them
		const std::string & cargo_name = cargo.get_name();
		const std::string & source = cargo.get_source();
		const std::string & destination = cargo.get_destination();
		//if not ship is capable of shipping this cargo, we print
		if (capable_ships.empty()) {
			std::cout << "No ships can carry the " << cargo_name << " from " << source << " to " << destination << "\n";
		}
		//if we do have some ships capable
		else {
			//we form a list alphabetically using sort and lamda expression
			std::sort(capable_ships.begin(),capable_ships.end(),[](const Ship * a, const Ship * b) {
					return a->get_name() < b->get_name();
			});
			std::cout << capable_ships.size() << " ships can carry the " << cargo_name << " from " << source << " to " << destination << "\n";
			//then load cargo one by one
			for (std::size_t i = 0; i < capable_ships.size(); i++) {
				std::cout << "  " << capable_ships[i]->get_name() << "\n";
			}
			//from the example loading onto The Majestic Dreadnought, so load to the first ship?
			Ship * target = capable_ships[0];
			target->load(cargo);
			//printing out the line
			std::cout << "**Loading the cargo onto " << target->get_name() << "**\n";
		}
	}
}

void print_and_destroy_ships(std::vector<Ship *> & ships) {
	// after loading, print out all the ship info
	std::cout << "---Done Loading---Here are the ships---\n";

	for (std::size_t i = 0; i < ships.size(); i++) {
	//unless the last one, need to have an empty line
		ships[i]->print_status();
		if (i < ships.size() - 1) {
			std::cout << "\n";
		}
	}
	//release
	for (std::size_t i = 0; i < ships.size(); i++) {
		delete ships[i];
	}
}

#endif

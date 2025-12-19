#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "cargo.hpp"
#include "cargo_parser.hpp"
#include "ship.hpp"
#include "ship_parser.hpp"
#include "avlmultimap11.hpp"
#include "main_functions.hpp"

//for convinience, typedef the avl thing
typedef AVLMultiMap<uint64_t, Ship *> ShipTree;

//have a method to find best ship
Ship * find_best_ship_for_cargo(const std::vector<Ship *> & ships, const Cargo & cargo) {
	ShipTree tree;

	//put some possible trees or shpis here into avl
	for (std::size_t i = 0; i < ships.size(); i++) {
		Ship * ship = ships[i];

		//check if capacity using my if_could_carry method
		if (!ship->if_could_carry(cargo)) {
			continue;
		}

		//calculate remaining space after loading it and add it. the smaller the better
		tree.add(ship->get_total_capacity() - ship->get_used_capacity() - cargo.get_weight(), ship);
	}

	//choose the better from trees
	//use the preOrderDump provided
	std::vector<std::pair<std::pair<uint64_t, std::set<Ship *> >, int> > dump = tree.preOrderDump();

	//if no ship can
	if (dump.empty()) {
		return NULL;
	}

	bool if_found_one = false;
	uint64_t best_remaining_space = 0;
	Ship * best_ship = NULL;

	for (std::size_t i = 0; i < dump.size(); i++) {
		uint64_t key_the_remaining = dump[i].first.first;
		const std::set<Ship *> & ship_set = dump[i].first.second;

		//skip to next loop if no
		if (ship_set.empty()) {
			continue;
		}

		//best currently according to aphabet in this group
		Ship * best_currently = NULL;
		//using iterator, must ++first
		for (std::set<Ship *>::const_iterator it = ship_set.begin(); it != ship_set.end(); ++it) {
			Ship * ship = *it;
			//empty then set the first or we look for smaller one
			if (best_currently == NULL || ship->get_name() < best_currently->get_name()) {
				best_currently = ship;
			}
		}
		if (!if_found_one) {
			//first find one
			if_found_one = true;
			best_remaining_space = key_the_remaining;
			best_ship = best_currently;
		}
		else {
			//found before pick the small value and replace
			if (key_the_remaining < best_remaining_space) {
				best_remaining_space = key_the_remaining;
				best_ship = best_currently;
			}
			else if (key_the_remaining == best_remaining_space) {
				//same remaining we determine by alphabetic order
				if (best_currently != NULL && best_currently->get_name() < best_ship->get_name()) {
					best_ship = best_currently;
				}
			}
		}
	}
	//possible that it is null
	return best_ship;
}

int main(int argc, char ** argv) {
	// must have three arguments
	if (argc != 3) {
		std::cerr << "You do not have enough arguments for step 4!\n";
		return EXIT_FAILURE;
	}

	//initialize the two parser classes and a vector of pointers for ships
	ShipParser ship_parser;
	CargoParser cargo_parser;
	std::vector<Ship *> ships;

	//use the extracted method
	if (!load_ships_from_file(argv[1], ship_parser, ships)) {
		return EXIT_FAILURE;
	}
	
	//use the extracted method for reading cargo
	std::ifstream cargo_input = read_cargo_file(argv[2], ships);
	
	//here different from step2 and step3 for new cargo functionalities
	std::vector<Cargo> cargos;
	std::string line;
	while (std::getline(cargo_input, line)) {
		if (line.empty()) {
			continue;
		}

		Cargo cargo = cargo_parser.parse_line(line);
		cargos.push_back(cargo);
	}
	//sort but keeping the original order if equal so use stable_sort
	std::stable_sort(cargos.begin(), cargos.end(), [](const Cargo & a, const Cargo & b) {
			return a.get_weight() > b.get_weight();
	});

	//look for proper ship for each cargo
	for (std::size_t i = 0; i < cargos.size(); i++) {
		const Cargo & each_cargo = cargos[i];
		Ship * best_ship = find_best_ship_for_cargo(ships, each_cargo);

		//for easier print, extract these
		const std::string & cargo_name = each_cargo.get_name();
		const std::string & source = each_cargo.get_source();
		const std::string & destination = each_cargo.get_destination();

		//not sure what to do if could not load, will modify if needed
		if (best_ship == NULL) {
			std::cout << "No ships can carry the " << cargo_name << " from " << source << " to " << destination << "\n";
		}
		else {
			uint64_t remaining_space =  best_ship->get_total_capacity() - best_ship->get_used_capacity();
			std::cout << "Loading " << cargo_name << " onto " << best_ship->get_name() << " from " << source << " to " << destination << " " 
				  << remaining_space - each_cargo.get_weight() << " capacity remains\n";
			//then load it
			best_ship->load(each_cargo);
		}
	}
	//use the extracted method for printing and clearing
	print_and_destroy_ships(ships);

	return EXIT_SUCCESS;	
}
	





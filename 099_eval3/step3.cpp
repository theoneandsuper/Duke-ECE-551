#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "cargo.hpp"
#include "ship.hpp"
#include "ship_parser.hpp"
#include "cargo_parser.hpp"
#include "main_functions.hpp"

int main(int argc, char ** argv) {
	//must have three arguments
	if (argc != 3) {
		std::cerr << "You do not have enough arguments for step 2!\n";
		return EXIT_FAILURE;
	}

	//initialize the two parser classes and a vector of pointers for ships
	ShipParser ship_parser;
	CargoParser cargo_parser;
	std::vector<Ship *> ships;
	
	//use the extracted method for loading ships
	if (!load_ships_from_file(argv[1], ship_parser, ships)) {
		return EXIT_FAILURE;
	}
	
	//use the extracted method for reading cargo
	//the returned will be used as the parameter for the extracted method for processing cargos
	std::ifstream cargo_input = read_cargo_file(argv[2], ships);
	process_cargo_stream(cargo_input, cargo_parser, ships);
	
	//use the extracted method for printing and clearing
	print_and_destroy_ships(ships);

	return EXIT_SUCCESS;
}

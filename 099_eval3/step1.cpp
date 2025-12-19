#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "route_map.hpp"
#include "ship_parser.hpp"

int main(int argc, char ** argv) {
	if (argc != 2) {
		std::cerr << "Argument number wrong!\n";
		return EXIT_FAILURE;
	}

	//initialize objects that needed to perform tast
	ShipParser ship_parser;
	RouteMap route_map;
	std::string line;

	//open the file
	std::ifstream input(argv[1]);
	if (!input) {
		std::cerr << "Could not open file!\n";
		return EXIT_FAILURE;
	}
	
	while (std::getline(input, line)) {
		//handling empty, for now let me assume empty line if fine
		if (line.empty()) {
			continue;
		}
		
		//building a ship
		Ship * ship_pointer = ship_parser.parse_line(line);
		Ship ship = *ship_pointer;
		//release
		delete ship_pointer;
		//adding this to recorded
		route_map.add_ship(ship);
	}

	route_map.print_routes();
	return EXIT_SUCCESS;
}

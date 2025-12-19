#ifndef ROUTE_MAP_HPP
#define ROUTE_MAP_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include "ship.hpp"

class RouteMap {
	std::set<std::string> recorded_names;
	//this is the one recording capacity for a specific rounte
	std::map<std::pair<std::string, std::string>, uint64_t> route_capacity;

	public:	
		void add_ship(const Ship & ship) {
			const std::string & name = ship.get_name();
			
			//see if we could see this name in the recorded, only add if it is not recorded
			if (recorded_names.count(name) > 0) {
				std::cerr << "You cannot have duplicate ships!\n";
				exit(EXIT_FAILURE);
			}
			recorded_names.insert(name);

			//upate the map value according to the key
			route_capacity[std::make_pair(ship.get_source(), ship.get_destination())] += ship.get_total_capacity();
		}

		void print_routes() const {
			for (std::map<std::pair<std::string, std::string>, uint64_t>::const_iterator it = route_capacity.begin(); it != route_capacity.end(); ++it) {
				std::cout << "(" << it->first.first << " -> " << it->first.second << ") has total capacity " << it->second << "\n";
			}
		}

};

#endif

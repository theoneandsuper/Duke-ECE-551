#ifndef CARGO_PARSER_HPP
#define CARGO_PARSER_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>
#include "cargo.hpp"
#include "utility_functions.hpp"

class CargoParser {
	private:
		Cargo check_and_fix_formality(const std::vector<std::string> & fields) const {
			//testing field number first
			if (fields.size() < 5) {
				std::cerr << "Cargo field number wrong!\n";
				std::exit(EXIT_FAILURE);
			}

			//testing capacity form using the method seperated out
			uint64_t weight = fix_and_return_uint64(fields[3]);

			//currently extra testing the name, source, destination must not be null (weight is tested with the fix method above already
			if (fields[0].empty() || fields[1].empty() || fields[2].empty()) {
				std::cerr << "Some of your fields are NULL, not allowed!\n";
				std::exit(EXIT_FAILURE);
			}

			//this one tests fields[4] and does other operations
			std::vector<std::string> properties;
			for (std::size_t i = 4; i < fields.size(); i++) {
				if (!fields[i].empty()) {
					properties.push_back(fields[i]);
				}
			}

			//we must have some properties
			if (properties.empty()) {
				std::cerr << "Your cargo doesnot have properties!\n";
				std::exit(EXIT_FAILURE);
			}

			return Cargo(fields[0], fields[1], fields[2], weight, properties);
		}


	public:
		Cargo parse_line(const std::string & input_line) const {
			//no need to handle errors as split_line has done it
			std::vector<std::string> fields = split_line(input_line, ',');
			//formality check and return
			return check_and_fix_formality(fields);
		}
};

#endif

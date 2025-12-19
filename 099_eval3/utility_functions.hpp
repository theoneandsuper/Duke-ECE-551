#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "ship.hpp"

std::vector<std::string> split_line(const std::string & line, char punctuation_mark) {
	std::vector<std::string> fields;
	std::size_t line_start = 0;
	
	while (true) {
		//keep looking for : until npos
		std::size_t mark_position = line.find(punctuation_mark, line_start);
		if (mark_position == std::string::npos) {
			fields.push_back(line.substr(line_start));
			break;
		}
		//adding the new substr
		fields.push_back(line.substr(line_start, mark_position - line_start));
		line_start = mark_position + 1;
	}

	return fields;
}

uint64_t fix_and_return_uint64(const std::string & string) {
	//one of the field check
	if (string.empty()) {
		std::cerr << "The numbers should not be null!\n";
		std::exit(EXIT_FAILURE);
	}
	std::size_t index = 0;
	uint64_t value = 0;
	//needs a try catch block in case there is format errors
	try {
		value = std::stoull(string, &index);
	}
	catch (...) {
		std::cerr << "Your number starts with non-digit!\n";
		std::exit(EXIT_FAILURE);
	}
	if (index != string.size()) {
		std::cerr << "Your number contains non-digit!\n";
		std::exit(EXIT_FAILURE);
	}
	return value;
}

#endif

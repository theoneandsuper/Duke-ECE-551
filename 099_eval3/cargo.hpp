#ifndef CARGO_HPP
#define CARGO_HPP

#include <cstdint>
#include <string>
#include <vector>

class Cargo {
	//as usual, the default is private
	std::string name;
	std::string source;
	std::string destination;
	uint64_t weight;
	std::vector<std::string> properties;

	public:
		Cargo(const std::string & name, const std::string & source, const std::string & destination, uint64_t weight, const std::vector<std::string> & properties) : 
		      name(name), source(source), destination(destination), weight(weight), properties(properties) {}

		const std::string & get_name() const {
			return name;
		}

		const std::string & get_source() const {
			return source;
		}

		const std::string & get_destination() const {
			return destination;
		}

		uint64_t get_weight() const {
			return weight;
		}

		const std::vector<std::string> & get_properties() const {
			return properties;
		}

		bool if_has_property(const std::string & property) const;	

		std::vector<std::string> extract_hazard_requirements() const;
};

#endif

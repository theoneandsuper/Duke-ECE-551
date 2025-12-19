#include <string>
#include "cargo.hpp"

bool Cargo::if_has_property(const std::string & property) const {
	//a classical for loop that looks for a specific property
	//one question here is what if property is named properties, will it be able to distinguish between them? Will ask if I remember
	for (std::size_t i = 0; i < properties.size(); i++) {
		if (properties[i] == property) {
			return true;
		}
	}
	return false;
}

std::vector<std::string> Cargo::extract_hazard_requirements() const {
	//this is the vector of all kinds of hazrd types to be returned
	std::vector<std::string> requirements;
	//might be used for several times later so let me declare this out
	const std::string prefix = "hazardous-";
	//another classical for loop that keeps extracting specific hazard requirements out
	for (std::size_t i = 0; i < properties.size(); i++) {
		if (properties[i].compare(0, prefix.size(), prefix) == 0) {
			requirements.push_back(properties[i].substr(prefix.size()));
		}
	}	
	return requirements;
}

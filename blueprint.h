#pragma once
#include <string>
#include <vector>


struct InfraBlueprint {
	std::string name;   // e.g., "security" , "input", "output", "etc."

	std::string style; // e.g., "OOP" or "Functional"
	

};

struct ProjectBlueprint {
	std::string projectName;
	std::vector<InfraBlueprint>
		infrastructures;
};
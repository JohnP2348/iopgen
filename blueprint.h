#pragma once
#include <string>
#include <vector>

struct ModuleBlueprint {
	std::string name;   // e.g., "securityModule", "inputHandler", "outputManager", etc.
	std::string style; // e.g., "OOP" or "Functional"
	std::string plugName; // e.g., "Security-AuthPlug", "Input-ParserPlug", "Output-FormatterPlug", etc.
};
struct InfraBlueprint {
	std::string name;   // e.g., "security" , "input", "output", "etc."

	std::vector<ModuleBlueprint> modules; // List of modules within this infrastructure
	
	
};

struct ProjectBlueprint {
	std::string projectName;
	std::vector<InfraBlueprint>
		infrastructures;
};
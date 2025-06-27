// cli_parser.cpp
#include <iostream>
#include "blueprint.h"

ProjectBlueprint collectBluePrintFromUser()
{
	ProjectBlueprint blueprint;
	std::cout << "Enter project name: ";
	std::getline(std::cin, blueprint.projectName);

	int count;
	std::cout << "How many infrastructure types will you define? ";
	std::cin >> count;
	std::cin.ignore(); // Clear the newline character from the input buffer

	for (int i = 0; i < count; i++) {
		InfraBlueprint infra;
		std::cout << "Enter infrastructure name (e.g., 'security', 'input', 'output'): ";
		std::getline(std::cin, infra.name);


		int moduleCount;
		std::cout << "How many modules will you define for " << infra.name << "? ";
		std::cin >> moduleCount;
		std::cin.ignore(); // Clear the newline character from the input buffer

		for (int j = 0; j < moduleCount; j++)
		{
			ModuleBlueprint module;
			std::cout << " Module/Class #" << (j + 1) << " Pick your paradigm: \n ('OOP', 'oop', 'Functional', or functional): ";
			std::getline(std::cin, module.style);
			std::cout << module.style << " name: ";
			std::getline(std::cin, module.name);
			infra.modules.push_back(module);
		}
		//std::cout << "Enter the coding style (e.g., 'OOP', 'Functional'): ";
		//std::getline(std::cin, infra.style);

		//std::cout << "Enter the class, function or module name (e.g., 'SecurityModule', 'InputHandler'): ";
		//std::getline(std::cin, infra.classOrModuleName);
		blueprint.infrastructures.push_back(infra);
	}
	return blueprint;
}
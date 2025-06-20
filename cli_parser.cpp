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

		std::cout << "Enter the coding style (e.g., 'OOP', 'Functional'): ";
		std::getline(std::cin, infra.style);

		blueprint.infrastructures.push_back(infra);
	}
	return blueprint;
}
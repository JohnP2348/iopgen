// iopgen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include "Scaffold_Builder.h"
#include "cli_parser.h"
#include "blueprint.h"

// Include the header file for the blueprint structure


int main()
{
    std::cout << "=== Welcome to IOPgen ===\n" << std::endl;

    ProjectBlueprint blueprint = collectBluePrintFromUser();

    std::cout << "\n[Blueprint Created]\n";
    std::cout << "Project: " << blueprint.projectName << "\n";
    for (const auto& infra : blueprint.infrastructures)
    {
        std::cout << " - " << infra.name << ":\n";
        for (const auto& module : infra.modules)
        {
            std::cout << "   - " << module.name << " (" << module.style << ")\n";
        }
    }
    
    // TODO: Pass this to scaffold_builder.cpp next
    generateInfrastructureFiles(blueprint);

    std::cout << "\n[Scaffold files generated.]\n";
	std::cout << "You can now start building your project with the generated files.\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

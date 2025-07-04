#include "Scaffold_Builder.h"
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <iostream>

#ifdef _WIN32
#include <direct.h> // For _mkdir
#endif


namespace {
	void createDirectory(const std::string& path)
	{
#ifdef _WIN32
		_mkdir(path.c_str());
#else
		mkdir(path.c_str(), 0755);
#endif
	}
	void writeFileLocal(const std::string& path, const std::string& content)
	{
		std::ofstream file(path);
		file << content;
		file.close();
	}
	void writeFile(const std::string& path, const std::string& content)
	{
		std::ofstream file(path);
		file << content;
		file.close();
	}

}

void generateInfrastructureFiles(const ProjectBlueprint& blueprint)
{
	createDirectory(blueprint.projectName); // Create the project root directory
	createDirectory(blueprint.projectName + "/infra"); // Create directory

	for (const auto& infra : blueprint.infrastructures)
	{
		std::string dir = blueprint.projectName + "/infra/" + infra.name;

		createDirectory(dir);



		for (const auto& module : infra.modules)
		{
			if (module.style == "OOP" || module.style == "oop")
			{
				std::string className = module.name;
				std::string headerPath = dir + "/" + className + ".h";
				std::string sourcePath = dir + "/" + className + ".cpp";

				std::string headerContent =
					"#pragma once\n"
					"#include <string>\n\n"
					"class " + className + " {\n"
					"public:\n"
					"    " + className + "();\n"
					"   ~" + className + "();\n"
					"    void exampleMethod();\n"
					"};\n";

				std::string sourceContent =
					"#include \"" + className + ".h\"\n\n"
					+ className + "::" + className + "() {}\n"
					+ className + "::~" + className + "() {}\n"
					"void " + className + "::exampleMethod() {} \n";

				writeFileLocal(headerPath, headerContent);
				writeFile(sourcePath, sourceContent);
			}
			else if (module.style == "Functional" || module.style == "functional")
			{
				std::string funcName = module.name;
				std::string headerPath = dir + "/" + funcName + ".h";
				std::string sourcePath = dir + "/" + funcName + ".cpp";

				std::string headerContent =
					"#pragma once\n"
					"#include <string>\n\n"
					"void " + funcName + "();\n";

				std::string sourceContent =
					"#include \"" + funcName + ".h\"\n\n"
					"void " + funcName + "() {\n"
					"    // Function implementation goes here\n"
					"}\n";

				writeFileLocal(headerPath, headerContent);
				writeFile(sourcePath, sourceContent);
			}
			// Plug files they are cpp and header files that make it easier to plug a class or module into a system.
			// Simply reference the class or module in the plug file. The plug is already pre plugged everywhere else in the program.
			// This makes it easier to plug in a module or class into a system without having to modify the existing code.
			std::string plugClassName = module.plugName; // e.g., "Security-AuthPlug" becomes "Security-AuthPlugPlug"
			std::string plugHeaderPath = dir + "/" + module.plugName + ".h";
			std::string plugSourcePath = dir + "/" + module.plugName + ".cpp";
			std::string plugHeaderContent;
			std::string plugSourceContent;

			if (module.style == "OOP" || module.style == "oop")
			{
				plugHeaderContent =
					"#pragma once\n"
					"#include \"" + module.name + ".h\"\n\n"
					"// Plug for " + infra.name + "/" + module.name + "\n"
					"class " + plugClassName + " {\n"
					"public:\n"
					"    " + plugClassName + "();\n"
					"    void use();\n"
					"private:\n"
					"    " + module.name + " instance;\n"
					"};\n";

				plugSourceContent =
					"#include \"" + plugClassName + ".h\"\n\n"
					+ plugClassName + "::" + plugClassName + "() {}\n"
					"void " + plugClassName + "::use() {\n"
					"    instance.exampleMethod();\n" // Call a method from the module
					"}\n";
		}
			else if (module.style == "Functional" || module.style == "functional")
			{
				plugHeaderContent =
					"#pragma once\n"
					"#include \"" + module.name + ".h\"\n\n"
					"// Plug for " + infra.name + "/" + module.name + "\n"
					"class " + plugClassName + " {\n"
					"public:\n"
					"    " + plugClassName + "();\n"
					"    void use();\n"
					"};\n";

				plugSourceContent =
					"#include \"" + plugClassName + ".h\"\n\n"
					+ plugClassName + "::" + plugClassName + "() {}\n"
					"void " + plugClassName + "::use() {\n"
					"    " + module.name + "();\n"
					"}\n";
			}
			// Write the plug header and source files
			writeFileLocal(plugHeaderPath, plugHeaderContent);
			writeFile(plugSourcePath, plugSourceContent);
			



		}

	}
	// Generate main.cpp in the project root
	std::string mainPath = blueprint.projectName + "/main.cpp";
	std::ofstream mainFile(mainPath);

	// IOP context for LLMs and any AI assistance systems
	mainFile <<
		R"(/*
                    IOP - Infrastructure Oriented Programming

					This file is auto-generated by IOPgen.This project uses the IOP framework, which treats code modules as infrastructure "plugs".
					Each plug (class) is easily swappable, making refactoring and maintenance simple.
					To change a module, just swap the plug in main.cpp�no spaghetti code, no deep rewrites.

					Plugs are declared below for each infrastructure module.
					To refactor, just change the plug assignment.

					For LLMs and developers: 
					 - Each #include below points to a module or plug.
					 - Each plug class wraps a module/class or function, and is the single point of integration.
					 - To swap implementations, change the plug instantiation.
					 - All code is organized by infrastructure (e.g., infra/security, infra/output).
					*/)" << "\n\n";

	mainFile << "#include <iostream>\n";
	// Include all plug headers with comments
	for (const auto& infra : blueprint.infrastructures) {
		for (const auto& module : infra.modules) {
			mainFile << "// Plug for " << infra.name << "/" << module.name << "\n";
			mainFile << "#include \"infra/" << infra.name << "/" << module.plugName << ".h\"\n";
		}
	}
	mainFile << "\nint main() {\n";
	mainFile << "    std::cout << \"IOP main.cpp: All plugs are ready to use.\\n\" << std::endl;\n";

	// Example usage of each plug
	for (const auto& infra : blueprint.infrastructures) {
		for (const auto& module : infra.modules) {
			mainFile << "    // Use plug for " << infra.name << "/" << module.name << "\n";
			mainFile << "    " << module.plugName << " plug_" << infra.name << "_" << module.name << ";\n";
			mainFile << "    plug_" << infra.name << "_" << module.name << ".use();\n";
		}
	}
	mainFile << "    return 0;\n}\n";
	mainFile.close();
}
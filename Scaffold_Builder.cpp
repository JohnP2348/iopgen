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
	void writeFile(const std::string& path, const std::string& content)
	{
		std::ofstream file(path);
		file << content;
		file.close();
	}

}

void generateInfrastructureFiles(const ProjectBlueprint& blueprint)
{
	createDirectory("infra");
	for (const auto& infra : blueprint.infrastructures)
	{
		std::string dir = "infra/" + infra.name;

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

				writeFile(headerPath, headerContent);
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
					"void" + funcName + "() {\n"
					"    // Function implementation goes here\n"
					"}\n";

				writeFile(headerPath, headerContent);
				writeFile(sourcePath, headerContent);
			}
		}
	}
}
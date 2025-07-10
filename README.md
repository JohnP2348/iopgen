IOP - Infrastructure Oriented Programming

IOP is a code framework designed to treat programming like infrastructure.
This allows for a more modular and flexible approach to programming, where components can be easily 
swapped out or upgraded without affecting the entire system.

Real-World Analogy:
- A TV plugs into your elctrical system.
- A toilet plugs into the plumbing system.
- A door lock plugs into the security system.

In the same way, IOP plugs code modules into infrastructure like:
- security
- output
- input
- auth
- UI
- database

Benefits:
- Plug and play modularity (swap components easily, just like plugging in a new TV or xbox)
- Easier upgrades (swap a module, not rewrite everything)
- Cleaner error handling per system
- Systemized file structure across any language
- More maintainable and understandable codebases
- The ability to update a module with a fallback switch case (e.g. V2 of the security module crashes the software so it fallsback to V1 of the security module.)

iopgen Tool:
The CLI tool 'iopgen' generates
infrastructure scaffolds for new modules,
ensuring your project follows IOP architecture
principles from the start.

What does IOPgen do?
IOPgen builds your project's architecture based on your upfront preplanned blueprint.
This ensures that your codebase starts off structured, modular, and easy to evolve in the long term.
First: Name your project
Second: Give the number of infrastructures you want to create
Third: Give the name of the first infrastructure
Fourth: Give the number of Modules/ classes you want to create (it supports functional and OOP).
Fifth: Tell it if the first Module/ class is a functional or OOP module.
Sixth: Give the name of the first Module/ class.
Seventh: Give the name of the plug for the first Module/ class. (This incorporates the name of the module/ class into the name of the infrastructure.)
(e.g. if the module is called "security" and the infrastructure is called "auth", the plug will be "authSecurityPlug".)
Eighth: Do steps five through seven for each additional Module/ class you chose to create. 
Then start at step three and repeat for each additional infrastructure you chose to create.

Generates : Header and source files for each module/class.
A matching plug file for each module/class that wraps the module/class in a plug that is named to match the infrastructure it plugs into.
This shows its relationship to the infrastructure. (like a TV plug into the electrical system.)

What is a plug?

A plug is a wrapper around a module or class that:
- Connects it to a specific infrastructure.
- Provides a consistent interface for that module/class.
- Allows for easy swapping of modules/classes without affecting the overall system.

How does it work?

Each plug connects to the main business logic.
When the programmer writes the logic, they call the plugs instead of the modules/classes directly.
This allows for:
- Main -> plug -> module/class instead of main -> module/class directly. Much like a house calling the electrical system to turn on the TV.
- Basically, call the plug to call the class/module plugged into it.
- Allowing a refactoring of main business logic without having to rewrite a codebase calling new modules/classes.
- Just simply go into the plug and change the module/class it calls.

Example:

Infrastructure: Security
Module/class: Authentication
Plug: AuthSecurityPlug

IOPgen is self documenting. 
After all of the infrastructure is built, it generates lowlevel context within a main.cpp it creates to give LLMs context on what the project is about.
It also includes all of the cpp and header files of the modules/classes and plugs it creates within main. Giving further context.
Each infrastructure has it's own file generated outside of main with the classes/modules and plugs within them. Generating the Heirarchy of the project.

How to refactor a codebase in IOP:

1. Identify the module/class you want to refactor.
2. Create a new version of the module/class (e.g. V2).
3. Update the plug to call the new version. 

Here is an example of how to refactor a security module:

What you start with:

CPP

#pragma once

#include "securityV1.h"

class SecurityCryptoPlug {

public:

	SecurityCryptoPlug() : securityV1(new SecurityV1()) {}
	void encryptData(const std::string& data) {
		securityV1->encryptData(data);
	}
	void decryptData(const std::string& data) {
		securityV1->decryptData(data);
		}
	}

	Change to

	#pragma once
	#include "securityV2.h"

	class SecurityCryptoPlug {
	public:
		SecurityCryptoPlug() : securityV2(new SecurityV2()) {}
		void encryptData(const std::string& data) {
			securityV2->encryptData(data);
		}
		void decryptData(const std::string& data) {
			securityV2->decryptData(data);
		}
	}

	Simple as that

	Now when you try to call SecurityCryptoPlug, it will call the new version of the security module/class.

	Why this works:

	This works because the plug acts as an intermediary between the main business logic and the module/class.

	This allows you to change the module/class without affecting the main business logic, just like plugging in a new TV without rewiring the entire house.

	Each plug is explicitly tied to a specific infrastructure, allowing for clear separation of concerns and modularity.

	Swapping out modules/classes is as simple as changing the plug to call the new version, without needing to rewrite the main business logic.

	The structure of IOP ensures that your codebase remains clean, maintainable, and easy to understand.
	
	It is self-documenting, making it easier for developers to onboard and understand the architecture.

	Refactoring is " Super easy, barely an inconvenience. "


	Future Roadmap and Ideas:

	Ability to create new infrastructures and modules/classes on the fly.

	Looking at fallback functionality for plugs, allowing them to revert to previous versions if the new version fails.
	Like a critical failure in a security module that causes the software to crash, allowing it to fall back to the previous version of the security module.
	like a switch case that allows the plug to call the previous version of the module/class if the new version fails.



Created By: John Patterson

"Don't tear down the house - just plug in the new tv."

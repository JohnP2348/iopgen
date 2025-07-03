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

Created By: John Patterson

"Don't tear down the house - just plug in the new tv."

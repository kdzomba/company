# company
COMPANY MENAGEMENT

Requires:
 - C++11 compiler (GCC)

Files included:
 - main.cpp
 - company.h
 - company.cpp
 - project.h
 - project.cpp
 - employees.h
 - globals.cpp

Description:
  Company is determined by a cost of hiring new employee.
  There are 4 categories of employees in the company: teamleaders, architects, engineers and testers.

 - Program enables following tasks:
	- 1. Hire new employee 
	- 2. Load employees from a text file
	- 3. Save employees to a text file
	- 4. Create a new project (with team consisted of 1 team leader, 1 architect and arbitrary number of engineers and testers)
	- 5. Display team ( employees working on given project)
	- 6. Get project cost
	- 7. Finish project (release the team and set project duration)

Compilation(Linux):
 $ g++ -std=c++11 -o prog  main.cpp company.cpp project.cpp  globals.cpp 
$ ./prog

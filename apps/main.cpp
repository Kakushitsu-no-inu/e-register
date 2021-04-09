#include "Group.h"
#include <iostream>

auto main() -> int
{
	Group KN_314 { 314 };
	KN_314.addStudent(Student { "Ivan", "Tkachuk" });
	KN_314.addStudent(Student { "Andrii", "Liashenko" });
	KN_314.addStudent(Student { "Florian", "Akostakioae" });
	KN_314.addStudent(Student { "Adi", "Akostakioae" });
	KN_314.addStudent(Student { "Vika", "Toporovska" });

	KN_314.saveToExcel("college.xlsx");

	Group K314 {};
	// Файл повинен бути відкритим
	K314.loadFromExcel("college.xlsx", 314);

    return 0;
}
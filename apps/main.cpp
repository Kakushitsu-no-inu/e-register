#include "Group.h"
#include <iostream>

auto main() -> int
{
	Group KN_314 { 314 };
	KN_314.addStudent(Student { "Ivan", "Tkachuk" });
	KN_314.addStudent(Student { "Andrii", "Liashenko" });
	KN_314.addStudent(Student { "Florian", "Akostakioae" });
	KN_314.addStudent(Student { "Smb", "Akostakioae" });

	KN_314.saveToExcel("college.excel");
}
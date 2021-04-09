#include "Group.h"
#include "Stuff.h"
#include <iostream>

auto main() -> int
{
	Teacher teacher { "Lazoryk", "Vasyl", "OOP" };

	Group KN_314 { 314 };
	Student stud1 { "Andrii", "Liashenko" };
	Student stud2 { "Ivan", "Tkachuk" };

	teacher.setMark(stud1, { 10 });
	teacher.setMark(stud2, {});

	KN_314.addStudent(stud1);
	KN_314.addStudent(stud2);

	KN_314.saveToExcel(std::to_string(314) + ".xlsx");
	KN_314.updateSubject(teacher.getSubject());

	return 0;
}
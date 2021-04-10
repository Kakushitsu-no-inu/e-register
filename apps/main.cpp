#include "Group.h"
#include "Stuff.h"
#include <iostream>

auto main() -> int
{
	Group KN_314 { 314 };
	Stuff clg {};

	clg.addTeacher(Teacher { "Vasyl", "Lazoryk", "OOP" });

	KN_314.addStudent(Student { "Andrii", "Liashenko" });
	KN_314.addStudent(Student { "Ivan", "Tkachuk" });

	auto& oop = clg.getTeacher("Lazoryk", "Vasyl");
	oop.setMark(KN_314.getStudent("Andrii", "Liashenko"), { 20 });
	oop.setMark(KN_314.getStudent("Ivan", "Tkachuk"), { 20 });
	oop.setMark(KN_314.getStudent("Andrii", "Liashenko"), { 30 });
	oop.setMark(KN_314.getStudent("Ivan", "Tkachuk"), { 30 });

	KN_314.updateSubject(oop.getSubject());
}
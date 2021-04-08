#include "Group.h"

Group::Group(int number) : number { number }
{}

void Group::addStudent(Student& stud)
{
	stud.setGroup(number);
	students.insert(stud);
}

bool Group::removeStudent(std::string_view name, std::string_view surname)
{
	Student toFind { name, surname, number };

	if (auto search = students.find(toFind); search != students.end())
	{
		students.erase(search);
		return true;
	}

	return false;
}

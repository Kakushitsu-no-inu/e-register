#include "Group.h"

Group::Group(int group) : group { group }
{}

void Group::addStudent(Student&& stud)
{
	stud.setGroup(group);
	students.insert(std::move(stud));
}

bool Group::removeStudent(std::string_view name, std::string_view surname)
{
	Student toFind { name, surname, group };

	if (auto search = students.find(toFind); search != students.end())
	{
		students.erase(search);
		return true;
	}

	return false;
}

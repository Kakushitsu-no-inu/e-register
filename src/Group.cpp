#include "Group.h"

Group::Group(int number) : number { number }
{}

void Group::addStudent(Student& stud)
{
<<<<<<< HEAD
	stud.setGroup(number);
	students.insert(stud);
||||||| dcfc690
	stud.setGroup(group);
	students.insert(std::move(stud));
=======
	stud.setGroup(group);
	students.insert(stud);
>>>>>>> 766a7e5063c5050cfca3c5d41dbaf7e0018b8f55
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

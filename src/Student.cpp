#include "Student.h"

Student::Student(std::string_view name) : Person { name }
{}

Student::Student(std::string_view name, std::string_view surname) : Person { name, surname }
{}

Student::Student(std::string_view name, std::string_view surname, int group) : Person { name, surname }, group { group }
{}

void Student::setGroup(int group)
{
	this->group = group;
}

const std::string& Student::getSurname() const
{
	return surname;
}

const std::string& Student::getName() const
{
	return name;
}
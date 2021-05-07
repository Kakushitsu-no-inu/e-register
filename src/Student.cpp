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

int Student::getGroup() const
{
	return group;
}

void Student::addMark(const std::string& subject, const Mark& mark) const 
{
	marks[subject].emplace_back(mark);
}

const Mark& Student::getMark(const std::string& subject) const
{
	return *(marks.at(subject).end() - 1);
}
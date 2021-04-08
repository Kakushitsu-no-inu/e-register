#pragma once
#include "Person.h"

class Student : public Person
{
public:
	Student() = default;

	Student(std::string_view name);

	Student(std::string_view name, std::string_view surname);

	Student(std::string_view name, std::string_view surname, int group);

	void setGroup(int group);

	std::string_view getSurname() const;

private:
	int group {};
};
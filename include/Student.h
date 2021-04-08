#pragma once
#include "Person.h"

class Student : public Person
{
public:
	Student() = default;

	Student(std::string_view name);

	Student(std::string_view name, std::string_view surname);

	Student(std::string_view name, std::string_view surname, int group);

<<<<<<< HEAD

||||||| dcfc690
	Student(const Student&& stud);

=======
>>>>>>> 766a7e5063c5050cfca3c5d41dbaf7e0018b8f55
	void setGroup(int group);

	std::string_view getSurname() const;

private:
	int group {};
};
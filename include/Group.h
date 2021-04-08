#pragma once
#include "Student.h"
#include <functional>
#include <set>

constexpr auto compareStuds = [](const Student& stud1, const Student& stud2) {
	return stud1.getSurname() < stud2.getSurname();
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsubobject-linkage"
class Group
{
public:
	Group(int group);

	void addStudent(Student&& stud);

	bool removeStudent(std::string_view name, std::string_view surname);

private:
	std::set<Student, decltype(compareStuds)> students { compareStuds };

	int group {};
};
#pragma GCC diagnostic pop
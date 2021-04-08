#pragma once
#include "Student.h"
#include <functional>
#include <set>
///компаратор для порівняння студентів (для алфавітної вставки)
constexpr auto compareStuds = [](const Student& stud1, const Student& stud2) {
	return stud1.getSurname() < stud2.getSurname();
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsubobject-linkage"
class Group
{
public:
	Group(int group);

	void addStudent(Student& stud);
	/**
 * @brief Видаляє студента з групи
 * 
 * @param name ім'я студента, якого видалити
 * @param surname прізвище студента, якого видалити
 * @return true  видалення успішне
 * @return false 
 */
	bool removeStudent(std::string_view name, std::string_view surname);

private:
	/// множина студентів
	std::set<Student, decltype(compareStuds)> students { compareStuds };

	int group {};
};
#pragma GCC diagnostic pop
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
	Group(int number);

	/**
	 * @brief Видаляє студента з групи 
	 * 
	 * @param name Ім'я студента
	 * @param surname Прізвище студента
	 * @return `true` якщо успішно видалено, `false` — якщо не знайдено студента
	 */
	void addStudent(const Student& stud);

	bool removeStudent(std::string_view name, std::string_view surname);

	void loadFromExcel(std::string_view filename);

	void saveToExcel(std::string_view filename);

private:
	// Множина студетнів
	std::set<Student, decltype(compareStuds)> students { compareStuds };

	// Номер групи
	int number {};
};
#pragma GCC diagnostic pop
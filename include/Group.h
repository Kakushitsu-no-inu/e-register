#pragma once
#include "Student.h"
#include <set>

constexpr auto compareStuds = [](const Student& stud1, const Student& stud2) {
	return stud1.getSurname() < stud2.getSurname();
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsubobject-linkage"
class Group
{
public:
	Group() = default;

	Group(int number);

	void addStudent(const Student& stud);

	/**
	 * @brief Видаляє студента з групи 
	 * 
	 * @param name Ім'я студента
	 * @param surname Прізвище студента
	 * @return `true` якщо успішно видалено, `false` — якщо не знайдено студента
	 */
	bool removeStudent(std::string_view name, std::string_view surname);

	void loadFromExcel(const std::string& filename, const std::string& number);

	void saveToExcel(const std::string& filename);

private:
	/// Множина студетнів
	std::set<Student, decltype(compareStuds)> students { compareStuds };
	/// Номер групи
	int number {};
	/// К-сть студентів
	int count {};
};
#pragma GCC diagnostic pop
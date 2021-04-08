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

<<<<<<< HEAD
	void addStudent(Student& stud);

	/**
	 * @brief Видаляє студента з групи 
	 * 
	 * @param name Ім'я студента
	 * @param surname Прізвище студента
	 * @return `true` якщо успішно видалено, `false` — якщо не знайдено студента
	 */
||||||| dcfc690
	void addStudent(Student&& stud);

=======
	void addStudent(Student& stud);
>>>>>>> 766a7e5063c5050cfca3c5d41dbaf7e0018b8f55
	bool removeStudent(std::string_view name, std::string_view surname);

private:
<<<<<<< HEAD
	// Множина студетнів
||||||| dcfc690
=======
	
>>>>>>> 766a7e5063c5050cfca3c5d41dbaf7e0018b8f55
	std::set<Student, decltype(compareStuds)> students { compareStuds };

	// Номер групи
	int number {};
};
#pragma GCC diagnostic pop
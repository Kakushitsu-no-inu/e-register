#pragma once
#include "Person.h"

/**
 * @class Student @file Student.h
 * 
 * @brief Клас, що описує Студента
 * 
 */
class Student : public Person
{
public:
	Student() = default;

	Student(std::string_view name);

	Student(std::string_view name, std::string_view surname);

	Student(std::string_view name, std::string_view surname, int group);

	/**
	 * @brief Встановлює студенту групу
	 * 
	 * @param group Номер групи для встановлення
	 */
	void setGroup(int group);

	/**
	 * @brief Функція дозволяє дізнатися групу студента
	 * 
	 * @return Номер групи 
	 */
	int getGroup() const;

private:
	int group {};
};
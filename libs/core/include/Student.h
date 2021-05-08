#pragma once
#include "Mark.h"
#include "Person.h"
#include <map>
#include <vector>

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

	/**
	 * @brief 
	 * 
	 * @param mark 
	 */
	void addMark(const std::string& subject, const Mark& mark) const;

	/**
	 * @brief Функція повертає останню оцінку з предмету
	 * 
	 * @return Оцінка
	 */
	const Mark& getMark(const std::string& subject) const;

private:
	int group {};
	mutable std::map<std::string, std::vector<Mark>> marks;
};


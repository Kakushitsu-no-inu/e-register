#pragma once
#include <string>

/**
 * @class Person @file Person.h
 * 
 * @brief Базовий клас, що описує людину
 * 
 */
class Person
{
public:
	Person() = default;

	Person(std::string_view name);

	Person(std::string_view name, std::string_view surname);

	/**
	 * @brief Повертає ім'я людини
	 * 
	 * @return Ім'я 
	 */
	const std::string& getName() const;

	/**
	 * @brief Повертає прізвище людини
	 * 
	 * @return Прізвище
	 */
	const std::string& getSurname() const;

protected:
	std::string name {};
	std::string surname {};
};
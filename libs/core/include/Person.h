#pragma once
#include <string>
#include <cstdint>
#include <exception>

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


class person_error : std::exception
{
public:
	person_error(const char* msg, const char* file, std::uint16_t line, const char* func_name, const char* info = "") :
		msg { msg },
		file { file },
		line { line },
		func_name { func_name },
		info { info }
	{}

	const char* what() const throw() override
	{
		return msg;
	}

	std::uint16_t get_line() const
	{
		return line;
	}

	const char* get_file() const
	{
		return file;
	}

	const char* get_func() const
	{
		return func_name;
	}

	const char* get_info() const
	{
		return info;
	}

private:
	const char* msg;
	const char* file;
	std::uint16_t line;
	const char* func_name;
	const char* info;
};
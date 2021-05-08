#pragma once
#include "Student.h"
#include <set>

class Group
{
public:
	Group() = default;

	Group(int number);
	/**
	 * @brief Функція додає студента в групу 
	 * 
	 * @param stud Об'єкт студента
	 */
	void addStudent(const Student& stud);

	/**
	 * @brief Видаляє студента з групи 
	 * 
	 * @param name Ім'я студента
	 * @param surname Прізвище студента
	 * @return `true` якщо успішно видалено, `false` — якщо не знайдено студента
	 */
	bool removeStudent(std::string_view name, std::string_view surname);

	[[nodiscard]] Student* getStudent(std::string_view name, std::string_view surname) const;

	/**
	 * @brief Функція зчитує групу з файлу EXCEL
	 * 
	 */
	void loadFromExcel();
	/**
	 * @brief Функція зчитує оцінки з файлу
	 * 
	 */
	void loadSubject(const std::string& subject);

	/**
	 * @brief Функція записує групу у файл EXCEL. 
	 * 		  Створює Аркуш з назвою номера групи
	 * 
	 * @param filename Ім'я файлу (з роширенням ".xlsx")
	 */
	void saveToExcel();

	/**
	 * @brief Функція оновлює дані про предмет
	 * 
	 * @param subject предмет
	 */
	void updateSubject(const std::string& subject);

	void setNumber(int number)
	{
		this->number = number;
	}

	int getNumber() const;

	void clear();

private:
	// Компаратор для студентів по їхньому прізвищу та імені в алфавітному порядку
	struct compare
	{
		bool operator()(const Student& stud1, const Student& stud2) const
		{
			return stud1.getSurname() < stud2.getSurname()
				|| (stud1.getSurname() == stud2.getSurname() && stud1.getName() < stud2.getName());
		}
	};

	/// Множина студетнів
	std::set<Student, compare> students {};
	/// Номер групи
	int number {};
	/// К-сть студентів
	int count {};
};

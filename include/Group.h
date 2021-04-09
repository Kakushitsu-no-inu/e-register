#pragma once
#include "Student.h"
#include <set>

//
constexpr auto compareStuds = [](const Student& stud1, const Student& stud2) {
	return stud1.getSurname() < stud2.getSurname();
};

// Виключаємо діагностику GCC на анонімні функції як шаблоний параметр
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

	/**
	 * @brief Функція зчитує групу з файлу EXCEL
	 * 
	 * @param filename Ім'я файлу (з роширенням .xlsx) 
	 * @param number Групу, яку треба зчитати
	 */
	void loadFromExcel(const std::string& filename, int number);

	/**
	 * @brief Функція записує групу у файл EXCEL. 
	 * 		  Створює Аркуш з назвою номера групи
	 * 
	 * @param filename Ім'я файлу (з роширенням .xlsx)
	 */
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
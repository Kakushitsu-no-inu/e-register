#pragma once
#include "student.h"
#include <set>

class group {
public:
  group() = default;

  group(int number);
  /**
   * @brief Функція додає студента в групу
   *
   * @param stud Об'єкт студента
   */
  void add_student(const student &stud);

  /**
   * @brief Видаляє студента з групи
   *
   * @param name Ім'я студента
   * @param surname Прізвище студента
   * @return `true` якщо успішно видалено, `false` — якщо не знайдено студента
   */
  bool remove_student(std::string_view name, std::string_view surname);

  [[nodiscard("Hold pointer")]] student *get_student(std::string_view name,
                                                     std::string_view surname) const;

  /**
   * @brief Функція зчитує групу з файлу EXCEL
   *
   */
  void load_from_excel();
  /**
   * @brief Функція зчитує оцінки з файлу
   *
   */
  void load_subject(const std::string &subject);

  /**
   * @brief Функція записує групу у файл EXCEL.
   * 		  Створює Аркуш з назвою номера групи
   *
   * @param filename Ім'я файлу (з розширенням ".xlsx")
   */
  void save_to_excel();

  /**
   * @brief Функція оновлює дані про предмет
   *
   * @param subject предмет
   */
  void update_subject(const std::string &subject);

  void set_number(int number) { this->number = number; }

  int get_number() const;

  void clear();

private:
  // Компаратор для студентів по їхньому прізвищу та імені в алфавітному порядку
  struct compare {
    bool operator()(const student &stud1, const student &stud2) const {
      return stud1.get_surname() < stud2.get_surname() ||
             (stud1.get_surname() == stud2.get_surname() && stud1.get_name() < stud2.get_name());
    }
  };

  /// Множина студентів
  // using student_set = std::set<student, compare>;
  std::set<student, compare> students{};
  /// Номер групи
  int number{};
  /// К-сть студентів
  int count{};
};

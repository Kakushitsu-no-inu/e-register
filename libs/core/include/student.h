#pragma once
#include "person.h"
#include <map>
#include <vector>

struct mark;

/**
 * @class student @file student.h
 *
 * @brief Клас, що описує Студента
 *
 */
class student : public person {
  using mark_map = std::map<std::string, std::vector<mark>>;
public:
  student() = default;

  student(std::string_view name);

  student(std::string_view name, std::string_view surname);

  student(std::string_view name, std::string_view surname, int group);

  /**
   * @brief Встановлює студенту групу
   *
   * @param group Номер групи для встановлення
   */
  void set_group(const int group);

  /**
   * @brief Функція дозволяє дізнатися групу студента
   *
   * @return Номер групи
   */
  const int get_group() const;

  /**
   * @brief
   *
   * @param mark
   */
  void add_mark(const std::string &subject, const mark &mark) const;

  /**
   * @brief Функція повертає останню оцінку з предмету
   *
   * @return Оцінка
   */
  const mark &get_last_mark(const std::string &subject) const;

  mark_map &get_marks();

  double average(const std::string &subject) const;

private:
  int group{};

  mutable mark_map marks{};
};

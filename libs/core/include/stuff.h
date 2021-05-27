#pragma once
#include "teacher.h"
#include <vector>

class stuff {
public:
  stuff() = default;

  /**
   * @brief Функція записує
   *
   */
  void save_to_file();

  void load_from_file();

  /**
   * @brief Функція додає нового викладача до колективу
   *
   * @param newTeacher Об'єкт викладач
   */
  void add_teacher(const teacher &new_teacher);

  // void deleteTeacher(std::string_view surname, std::string_view name);

 teacher *get_teacher(std::string_view surname, std::string_view name);

  teacher *sign_in(const std::string &password);

private:
  using teacher_list = std::vector<teacher>;
  teacher_list teachers;
};

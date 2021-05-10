#pragma once
#include "person.h"
 
#include <istream>

class student;

/**
 * @class Teacher @file Teacher.h
 *
 * @brief Клас описує вчителя
 *
 */
class teacher : public person {
public:
  teacher() = default;

  teacher(std::string_view name, std::string_view surname);

  teacher(std::string_view name, std::string_view surname, std::string_view subject);

  teacher(std::string_view name, std::string_view surname, std::string_view subject,
          std::string password);

  void set_password(const std::string &password);

  const std::string &get_subject() const;

  const std::string &get_password() const;

  void set_mark(student &stud, std::string_view value) const;

  friend std::istream &operator>>(std::istream &is, teacher &t);

private:
  std::string subject{};
  std::string password{};
};

#pragma once
#include <string>
#include <cstdint>
#include <exception>

/**
 * @class person @file person.h
 *
 * @brief Базовий клас, що описує людину
 *
 */
class person {
public:
  person() = default;

  person(std::string_view name);

  person(std::string_view name, std::string_view surname);

  /**
   * @brief Повертає ім'я людини
   *
   * @return Ім'я
   */
  const std::string &get_name() const;

  /**
   * @brief Повертає прізвище людини
   *
   * @return Прізвище
   */
  const std::string &get_surname() const;

protected:
  std::string name{};
  std::string surname{};
};

class person_error : std::exception {
public:
  person_error(const char *msg) : msg{msg} {}

  const char *what() const throw() override { return msg; }

private:
  const char *msg;
};

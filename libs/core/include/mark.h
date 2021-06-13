#pragma once
#include <ctime>
#include <string>

/**
 * @struct mark @file mark.h
 * @brief Структура пресдатвляє собою оцінку
 *
 */
struct mark {
  std::string value{"0"};
  std::string subject{};
  std::tm     date{};
  size_t id{};

  static size_t count;

  mark(std::string_view value, std::string_view subject, const std::tm &date);

  /**
   * @brief Функція повертає дату у форматі %d.%m.%Y (НаприклаД: 03.04.2020)
   *
   * @return Дату у форматі рядок
   */
  std::string time_to_string() const;
};

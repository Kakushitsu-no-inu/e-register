// clang-format off
#include "teacher.h"
#include "student.h"
#include "mark.h"
// clang-format on

teacher::teacher(std::string_view name, std::string_view surname) : person(name, surname) {}

teacher::teacher(std::string_view name, std::string_view surname, std::string_view subject)
  : person(name, surname), subject(subject) {}

teacher::teacher(std::string_view name, std::string_view surname, std::string_view subject,
                 std::string password)
  : person(name, surname), subject(subject), password(password) {}

void teacher::set_password(const std::string &password) { this->password = password; }

const std::string &teacher::get_subject() const { return subject; }

const std::string &teacher::get_password() const { return password; }

void teacher::set_mark(student &stud, std::string_view value) const {
  std::time_t now{std::time(nullptr)};
  std::tm *   date{std::localtime(&now)};

  stud.add_mark(this->subject, mark{value, this->subject, *date});
}

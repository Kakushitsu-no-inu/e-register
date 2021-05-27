#include "student.h"
#include "mark.h"

student::student(std::string_view name) : person{name} {}

student::student(std::string_view name, std::string_view surname) : person{name, surname} {}

student::student(std::string_view name, std::string_view surname, int group)
  : person{name, surname}, group{group} {}

void student::set_group(const int group) { this->group = group; }

const int student::get_group() const { return group; }

void student::add_mark(const std::string &subject, const mark &mark) const {
  if(marks[subject].empty())
    marks[subject].emplace_back(mark);
  else if (marks[subject].back().time_to_string() != mark.time_to_string())
    marks[subject].emplace_back(mark);
}

const mark &student::get_last_mark(const std::string &subject) const {
  return *(marks.at(subject).end() - 1);
}

#include "student.h"
#include "mark.h"
#include <numeric>

student::student(std::string_view name) : person{name} {}

student::student(std::string_view name, std::string_view surname) : person{name, surname} {}

student::student(std::string_view name, std::string_view surname, int group)
  : person{name, surname}, group{group} {}

void student::set_group(const int group) { this->group = group; }

const int student::get_group() const { return group; }

void student::add_mark(const std::string &subject, const mark &mark) const {
  if (marks[subject].empty())
    marks[subject].emplace_back(mark);
  else if (marks[subject].back().time_to_string() != mark.time_to_string())
    marks[subject].emplace_back(mark);
}

const mark &student::get_last_mark(const std::string &subject) const {
  return *(marks.at(subject).end() - 1);
}

student::mark_map &student::get_marks() { return marks; }

void student::change_mark(const std::string &subject, const std::string &time, const std::string &value) {
  auto vec = marks[subject];
  auto it = std::find_if(vec.begin(), vec.end(), [&](const mark &m) {
    return m.time_to_string() == time;
  });

  if (it != std::end(vec))
    it->value = value;
}

double student::average(const std::string &subject) const {
  auto &vec = marks[subject];
  bool  is_number{};

  if (vec[0].value.find_first_of("0123456789") != std::string::npos)
    is_number = true;

  auto avg = std::accumulate(vec.begin(), vec.end(), 0.0, [&](double sum, const mark &m) {
    if (is_number)
      return sum + std::stof(m.value);
    return sum;
  });

  return avg / vec.size();
}

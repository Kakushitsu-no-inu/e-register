// clang-foramt off
#include "config.h"
#include "stuff.h"
#include "student.h"
#include "mark.h"
// clang-format on
#include <algorithm>
#include <fstream>

void stuff::save_to_file() {
  std::ofstream file{config::STUFF_FILE, std::ios::out};
  if (file.good()) {
    std::for_each(teachers.begin(), teachers.end(), [&file](const teacher &teach) {
      file << teach.get_surname() << ' ' << teach.get_name() << ' ' << teach.get_subject() << ' '
           << teach.get_password() << '\n';
    });
  }

  file.close();
}

void stuff::load_from_file() {
  std::ifstream file{config::STUFF_FILE, std::ios::in};
  if (!file.good()) {
    throw std::runtime_error{"Can't open file!"};
  }

  std::string name{}, surname{}, subject{}, password{};
  while (file >> name >> surname >> subject >> password) {
    add_teacher(teacher{name, surname, subject, password});
  }
  file.close();
}

void stuff::add_teacher(const teacher &new_teacher) { teachers.emplace_back(new_teacher); }

const teacher &stuff::get_teacher(std::string_view surname, std::string_view name) const {
  if (auto find = std::find_if(teachers.begin(), teachers.end(),
                               [&](const teacher &teach) {
                                 return teach.get_surname() == surname && teach.get_name() == name;
                               });
      find != teachers.end()) {
    return *find;
  }
  throw person_error{"not found teacher"};
}

teacher *stuff::sign_in(const std::string &password) {
  if (auto it = std::find_if(teachers.begin(), teachers.end(),
                             [&](const teacher &t) { return t.get_password() == password; });
      it != teachers.end()) {
    return &(*it);
  }
  throw person_error{"not found teacher"};
}

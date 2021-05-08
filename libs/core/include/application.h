#pragma once

// clang-format off
#include "stuff.h"
#include "group.h"
#include "mark.h"
// clang-format on
#include "ui.h"
#include "utils.hpp"

class application {
public:
  static application &get_instance();

  void run();

private:
  application();

  auto init() -> menu<stage<3UL>, stage<3UL>, stage<2UL>, stage<5UL>>;

  bool sign_in_teacher();
  bool sign_in_stud();

  bool select_group();
  void change_password();

  void quit();

  void show_mark(const student &stud);

  stuff m_stuff;
  group m_group;

  teacher *m_current_teacher{};
  student *m_current_student{};

  menu<stage<3UL>, stage<3UL>, stage<2UL>, stage<5UL>> m_menu;
};

#pragma once

#include "Group.h"
#include "Stuff.h"
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

  void show_mark(const Student &stud);

  Stuff m_stuff;
  Group m_group;

  Teacher *                                            m_current_teacher{};
  Student *                                            m_current_student{};
  menu<stage<3UL>, stage<3UL>, stage<2UL>, stage<5UL>> m_menu;
};

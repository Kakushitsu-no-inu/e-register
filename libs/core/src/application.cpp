#include "application.h"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <cstddef>

application::application()
  : m_menu{std::move(init())}, m_current_teacher{nullptr}, m_current_student{nullptr} {}

application &application::get_instance() {
  static application self;
  return self;
}

void application::run() {
  while (true) {
    m_menu.print();
    size_t choice;
    std::cin >> choice;
    m_menu.handle(choice - 1);
    std::cout << '\n';
  }
}

auto application::init() -> menu<stage<3UL>, stage<3UL>, stage<2UL>, stage<5UL>> {
  m_stuff.load_from_file();

  auto sing_in = make_window(
    "Sign In",
    option{[&](menu_base *menu) {
             if (sign_in_teacher()) {
               std::cout << "\nYou are sign in as "
                         << m_current_teacher->get_name() + " " + m_current_teacher->get_surname() +
                              " [" + m_current_teacher->get_subject() + "]\n";
               menu->switch_window(1);
             } else {
               std::cout << "\nBad password!\n";
             }
           },
           "as Teacher"},
    option{[&](menu_base *menu) {
             if (sign_in_stud()) {
               menu->switch_window(2);
             }
           },
           "as Student"},
    option{[&](menu_base *) { quit(); }, "Exit"}
    /*option([&](menu_base *menu) { if (signInAdmin()) { menu->switch_window(4); } }) */
  );

  auto student_menu = make_window(
    "Student Options", option{[&](menu_base *) { show_mark(*m_current_student); }, "Show Marks"},
    option{[&](menu_base *) { quit(); }, "Exit"});

  auto teacher_menu =
    make_window("Teacher Options",
                option{[&](menu_base *menu) {
                         if (select_group()) {
                           menu->switch_window(3);
                         } else {
                           std::cout << "Bad number group!!! Try again.\n";
                         }
                       },
                       "Select group"},
                option{[&](menu_base *) { change_password(); }, "Change Password"},
                option{[&](menu_base *menu) {
                         m_current_teacher = nullptr;
                         menu->switch_window(0);
                       },
                       "Log Out"});

  auto group_menu = make_window(
    "What to do?",
    option{[&](menu_base *) { std::cout << fmt::format("{}\n", m_group); }, "Show Students"},
    option{[&](menu_base *) { /* setMarkStudent(); */ }, "Set Student's Mark"},
    option{[&](menu_base *) { /* setAllMarks(); */ }, "Set Students' Marks"},
    option{[&](menu_base *) { /* changeMark(); */ }, "Change Student's Mark"},
    option{[&](menu_base *menu) {
             m_current_student = nullptr;
             menu->switch_window(1);
           },
           "Return"});

  /* auto admin_menu = */
  return make_menu(sing_in, teacher_menu, student_menu, group_menu /*, admin_menu */);
}

void application::change_password() {
  std::cout << "Enter new password: ";
  std::string password = input_password(std::cin);
  m_current_teacher->set_password(password);
}

void application::quit() {
  m_stuff.save_to_file();
  exit(EXIT_SUCCESS);
}

bool application::select_group() {
  int number;
  std::cout << "Enter number group: ";
  std::cin >> number;
  if (std::cin.bad()) {
    return false;
  } else {
    try {
      m_group.load_from_excel();
      return true;
    } catch (...) {
      return false;
    }
  }
}

bool application::sign_in_stud() {
  if (select_group()) {
    std::cout << "Enter your name and surname: ";
    std::string name, surname;
    std::cin >> name >> surname;

    try {
      m_current_student = m_group.get_student(name, surname);
      return true;
    } catch (person_error &err) {
      return false;
    }
  }
  return false;
}

bool application::sign_in_teacher() {
  std::cout << "Enter password: ";
  std::string password = input_password(std::cin);

  try {
    m_current_teacher = m_stuff.sign_in(password);
    return true;
  } catch (person_error &err) {
    return false;
  }
}

void application::show_mark(student const &) {}

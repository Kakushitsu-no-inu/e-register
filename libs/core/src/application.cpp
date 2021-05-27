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

auto application::init() -> menu<stage<4UL>, stage<3UL>, stage<2UL>, stage<4UL>, stage<3UL>> {

  try {
    m_stuff.load_from_file();
  } catch (const std::exception &err) {
    std::cerr << err.what() << '\n';
    std::cerr << "First Create Data Base of Teachers!!!\n";
  }

  auto sing_in = make_window("Sign In",
                             option{[&](menu_base *menu) {
                                      if (sign_in_teacher()) {
                                        std::cout << "\nYou are sign in as "
                                                  << m_current_teacher->get_name() + " " +
                                                       m_current_teacher->get_surname() + " [" +
                                                       m_current_teacher->get_subject() + "]\n";
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
                             option{[&](menu_base *menu) { menu->switch_window(4); }, "as Admin"},
                             option{[&](menu_base *) { quit(); }, "Exit"});

  auto student_menu = make_window(
    "Student Options", option{[&](menu_base *) { show_mark(); }, "Show Marks"},
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
    option{[&](menu_base *) { set_mark_student(); }, "Set Student's Mark"},
    option{[&](menu_base *) { set_all_marks(); }, "Set Students' Marks"},
    option{[&](menu_base *menu) {
             auto &cache = cache_group.get_students();
             for (auto &students = m_group.get_students(); auto &stud : students) {
               auto It = cache.find(stud);
               if(It == cache.end())
                 m_current_teacher->set_mark(stud, " ");
             }
             m_group.update_subject(m_current_teacher->get_subject());
             m_current_student = nullptr;
             menu->switch_window(1);
           },
           "Return"});

  auto admin_menu =
    make_window("Admin Options", option{[&](menu_base *) { add_teacher(); }, "Add Teacher"},
                option{[&](menu_base *) { add_group(); }, "Add Group"},
                option{[&](menu_base *) { quit(); }, "Exit"});
  return make_menu(sing_in, teacher_menu, student_menu, group_menu, admin_menu);
}

void application::set_mark_student() {
  
  std::cout << fmt::format("{}\n", m_group);
  std::string name, surname;
  std::cout << "Student's name and surname: ";
  std::cin >> name >> surname;

  auto &stud = *m_group.get_student(name, surname);

  std::string value;
  std::cout << "Enter mark: ";
  std::cin >> value;
  m_current_teacher->set_mark(stud, value);
  cache_group.add_student(student{name,surname});
}

void application::set_all_marks() {
  // try {
  //   m_group.load_subject(m_current_teacher->get_subject());
  // } catch (...) {
  //   std::cerr << "Not found DataBase for your subject! Creating... \n";
  // }

  for (auto &students = m_group.get_students(); auto &stud : students) {
    std::string value;
    std::cout << "Enter mark for " << stud.get_name() << " " << stud.get_surname() << ": ";
    std::cin >> value;
    m_current_teacher->set_mark(stud, value);
  }

  // m_group.update_subject(m_current_teacher->get_subject());
}



void application::add_group() {
  int   number;
  group g;

  std::cout << "Enter group's number: ";
  std::cin >> number;

  g.set_number(number);

  std::string name, surname;

  std::cout << "Add student <name> <surname>. Press 0 to end input.\n";
  while (true) {
    std::cin >> name >> surname;
    if (name == "0" || surname == "0")
      break;
    g.add_student(student{name, surname});
  }

  g.save_to_excel();
}

void application::add_teacher() {
  teacher t;
  std::cout << "Enter teacher info <name> <surname> <subject> <password>\n";
  std::cin >> t;
  m_stuff.add_teacher(t);
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
  m_group.clear();
  cache_group.clear();
  m_group.set_number(number);
  cache_group.set_number(number);
  try {
    m_group.load_from_excel();
    m_group.load_subject(m_current_teacher->get_subject());
    return true;
  } catch (std::exception &err) {
    std::cerr << err.what() << '\n';
    return false;
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

void application::show_mark() {
    for (auto &map = m_current_student->get_marks(); auto &[subject, marks] : map) {
        std::cout << subject << ' ';
        for (auto &mark : marks) {
            std::cout << mark.value << ' ';
        }
        std::cout << std::endl;
    }
}

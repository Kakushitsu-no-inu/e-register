#include "college.h"

int main()
{}

// std::string nameStudent = "Student 1";
// 	size_t mark = 30;
// 	auto w1 = make_window("Main Menu",
// 		"",
// 		Option([](IMenu* menu) { menu->switchWindow(1); }, "Menu 1"),
// 		Option([](IMenu*) { exit(0); }, "Exit"));
// 	auto w2 = make_window("Menu 1",
// 		"",
// 		Option(
// 			[&](IMenu*) {
// 				std::cout << "Enter new mark: ";
// 				std::cin >> mark;
// 				std::cout << "New mark is " << mark << "\n";
// 			},
// 			"Set Mark"),
// 		Option(
// 			[&](IMenu*) {
// 				std::cout << "Enter new name student: ";
// 				std::cin >> nameStudent;
// 				std::cout << "New name is " << nameStudent << '\n';
// 			},
// 			"Set New Name"),
// 		Option([&](IMenu*) { std::cout << nameStudent << " " << mark << '\n'; }, "Print info"),
// 		Option([](IMenu* menu) { menu->switchWindow(0); }, "Return"));

// 	auto menu = make_menu(w1, w2);
// 	while (true)
// 	{
// 		menu.print();
// 		size_t choice;
// 		std::cin >> choice;
// 		choice--;
// 		menu.handle(choice);
// 		std::cout << '\n';
// 	}
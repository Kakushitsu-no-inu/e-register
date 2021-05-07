#include "college.h"

void College::init()
{
	stuff.loadFromFile();

	auto sing_in = make_window("Sign In",
		"",
		Option(
			[&](IMenu* menu) {
				std::cout << "Enter password: ";
				std::string password = input_password();
				signIn(password);
				menu->switchWindow(1);
			},
			"as Teacher"),
		Option([&](IMenu* menu) { menu->switchWindow(2); }, "as Student"),
		Option([&](IMenu*) { exit(0); }, "Exit"));
	
	// auto teacher_menu = make_window("Teacher Options",
	// 	std::string(
	// 		"You are sign in " + current.getName() + " " + current.getSurname() + " [" + current.getSubject() + "]")
	// 		.c_str(),
	// 	Option([&](IMenu *menu) { 
	// 		std::cout << ""

	// 	}));
}

void College::signIn(const std::string& password)
{
	current = stuff.signIn(password);
}

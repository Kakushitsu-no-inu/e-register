#include "college.h"

void College::run()
{
	while (true)
	{
		menu.print();
		size_t choice;
		std::cin >> choice;
		menu.handle(choice - 1);
		std::cout << '\n';
	}
}

auto College::init() -> Menu<Window<3UL>, Window<3UL>, Window<2UL>, Window<5UL>>
{
	stuff.loadFromFile();

	// clang-format off
	auto sing_in = make_window("Sign In", "",
		Option([&](IMenu* menu) { if (signInTeacher()) { menu->switchWindow(1); } else { std::cout << "Bad password!\n"; } },
			"as Teacher"),
		Option([&](IMenu* menu) { if (signInStudent()) { menu->switchWindow(2); } }, "as Student"),
		Option([&](IMenu*) { exit(EXIT_SUCCESS); }, "Exit")
		/*Option([&](IMenu *menu) { if (signInAdmin()) { menu->switchWindow(4); } }) */);

	auto student_menu = make_window("Student Options",
		std::string("You are sign in " + currStudent->getName() + " " + currStudent->getSurname()).c_str(),
		Option([&](IMenu *) { showMark(*currStudent); }, "Show Marks"),
		Option([&](IMenu *) { exit(EXIT_SUCCESS); }, "Exit"));

	auto teacher_menu = make_window("Teacher Options",
		std::string("You are sign in " + currTeacher->getName() + " " + currTeacher->getSurname() + " [" + currTeacher->getSubject() + "]").c_str(),
		Option([&](IMenu* menu) { if (selectGroup()) { menu->switchWindow(3); } else { std::cout << "Bad number group!!! Try again.\n"; } },
			"Select group"),
		Option([&](IMenu*) { changePassword(); }, "Change Password"),
		Option([&](IMenu* menu) { currTeacher = nullptr; menu->switchWindow(0); }, "Log Out"));

	auto group_menu = make_window("What to do?", "",
		Option([&](IMenu*) { /* group.show(); */ }, "Show Students"),
		Option([&](IMenu*) { /* setMarkStudent(); */ }, "Set Student's Mark"),
		Option([&](IMenu*) { /* setAllMarks(); */ }, "Set Students' Marks"),
		Option([&](IMenu*) { /* changeMark(); */ }, "Change Student's Mark"),
		Option([&](IMenu* menu) { currStudent = nullptr; menu->switchWindow(1); }, "Return"));

	/* auto admin_menu = */
	// clang-format on
	return make_menu(sing_in, teacher_menu, student_menu, group_menu /*, admin_menu */);
}

void College::changePassword()
{
	std::cout << "Enter new password: ";
	std::string password = input_password();
	currTeacher->setPassword(password);
}

bool College::selectGroup()
{
	int number;
	std::cout << "Enter number group: ";
	std::cin >> number;
	if (std::cin.bad())
	{
		return false;
	}
	else
	{
		try
		{
			group.loadFromExcel();
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
}

bool College::signInStudent()
{
	if (selectGroup())
	{
		std::cout << "Enter your name and surname: ";
		std::string name, surname;
		std::cin >> name >> surname;

		try
		{
			*currStudent = group.getStudent(name, surname);
			return true;
		}
		catch (person_error& err)
		{
			return false;
		}
	}
	return false;
}

bool College::signInTeacher()
{
	std::cout << "Enter password: ";
	std::string password = input_password();

	try
	{
		*currTeacher = stuff.signIn(password);
		return true;
	}
	catch (person_error& err)
	{
		return false;
	}
}

void College::showMark(Student const&)
{}
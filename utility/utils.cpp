#include "utils.hpp"

#ifdef _WIN32
	#include <time.h>
	#include <sstream>
	#include <windows.h>
#elif __linux__
	#include <termios.h>
#endif

#include <iostream>

#ifdef _WIN32
char* strptime(const char* s, const char* f, struct tm* tm)
{
	std::istringstream input(s);
	input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
	input >> std::get_time(tm, f);
	if (input.fail())
	{
		return nullptr;
	}
	return (char*)(s + input.tellg());
}

void pause()
{
	system("pause");
}
#endif

void cls()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}

static void echo(bool _mode)
{
#ifdef __WIN32
	DWORD mode;
	HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hConIn, &mode);
	mode = _mode ? (mode | ENABLE_ECHO_INPUT) : (mode & ~(ENABLE_ECHO_INPUT));
	SetConsoleMode(hConIn, mode);
#elif __linux__
	struct termios settings;
	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag = _mode ? (settings.c_lflag | ECHO) : (settings.c_lflag & ~(ECHO));
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
#endif
}

std::string input_password()
{
	std::string password { "" };
	echo(0x0);
	std::getline(std::cin, password);
	echo(0x1);
	return password;
}
#pragma once
#include <string>

#include <time.h>

#ifdef _WIN32
#include <iomanip>
#include <sstream>
	#include <windows.h>
#elif __linux__
	#include <termios.h>
	#include <unistd.h>
#endif

#ifdef _WIN32
extern "C" char* strptime(const char* s, const char* f, struct tm* tm)
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
#endif

void Pause()
{
#ifdef _WIN32
	system("pause");
#elif __linux__
	pause();
#endif
}

void clrscr()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}

namespace Utility
{
enum EchoMode
{
	OFF = 0x0,
	ON = 0x1,
};

void echo(bool _mode)
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

std::string InputPassword(std::istream& in)
{
	std::string password {};
	echo(EchoMode::OFF);
	std::getline(in, password);
	echo(EchoMode::ON);
	return password;
}
}
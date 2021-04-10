#pragma once
#include <string>

#ifdef _WIN32
	#include <windows.h>

namespace Utility
{
enum EchoMode
{
	OFF = 0x0,
	ON = 0x1,
};

void SetEchoMode(bool _mode)
{
	DWORD mode;
	HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hConIn, &mode);
	mode = _mode ? (mode | ENABLE_ECHO_INPUT) : (mode & ~(ENABLE_ECHO_INPUT));
	SetConsoleMode(hConIn, mode);
}

void SetEchoMode(bool _mode)
{
	DWORD mode;
	HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hConIn, &mode);
	mode = _mode ? (mode | ENABLE_ECHO_INPUT) : (mode & ~(ENABLE_ECHO_INPUT));
	SetConsoleMode(hConIn, mode);
}

std::string InputPassword(std::istream& in)
{
	std::string password {};
	SetEchoMode(EchoMode::OFF);
	std::getline(in, password);
	SetEchoMode(EchoMode::ON);
	return password;
}
}
#endif
#pragma once
#include <string>
#include <istream>

#ifdef _WIN32
char *strptime(const char *S, const char *f, struct tm *tm);
#endif

void pause_();

void cls();

std::string input_password(std::istream &is);

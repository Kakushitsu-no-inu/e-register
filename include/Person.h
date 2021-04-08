#pragma once
#include <string>

class Person
{
public:
	Person() = default;

	Person(std::string_view name);

	Person(std::string_view name, std::string_view surname);

protected:
	std::string name {};
	std::string surname {};
};
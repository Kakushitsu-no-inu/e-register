#pragma once
#include <string>

namespace erg
{
class Person
{
public:
	Person() = default;

	Person(std::string_view name);

	Person(std::string_view name, std::string surname);

protected:
	std::string name {};
	std::string surname {};
};
}
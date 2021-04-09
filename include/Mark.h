#pragma once
#include <ctime>
#include <optional>
#include <string>

struct Mark
{
	std::optional<int> value { std::nullopt };
	std::string subject {};
	std::tm date {};

	std::string getDate()
	{
		char c[9];
		std::strftime(c, 9, "%d/%m/%y", &date);
		return std::string { c };
	}
};
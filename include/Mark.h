#pragma once
#include <ctime>
#include <optional>
#include <string>

struct Mark
{
	std::optional<int> value { std::nullopt };
	std::string subject {};
	std::tm date {};

	Mark(std::optional<int> value, std::string_view subject, const std::tm& date) :
		value { value },
		subject { subject },
		date { date }
	{}

	std::string getDate() const
	{
		char c[12];
		std::strftime(c, 12, "%d.%m.%Y", &date);
		return std::string { c };
	}
};
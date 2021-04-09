#pragma once
#include <ctime>
#include <optional>
#include <string>

struct Mark
{
	std::optional<int> value { std::nullopt };
	std::string subject {};
	std::tm date {};
};
#pragma once

#include "menu.h"
#include <functional>
#include <utility>

struct Option
{
	using Callback = std::function<void(IMenu*)>;

	Callback callback;
	const char* text;

	Option(Callback callback, const char* text) : callback(std::move(callback)), text(text)
	{}
};
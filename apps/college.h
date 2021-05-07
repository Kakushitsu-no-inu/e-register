#pragma once

#include "Group.h"
#include "Stuff.h"
#include "ui.h"
#include "utils.hpp"

class College
{
public:
	College();

	void signIn(const std::string& password);

private:
	void init();

	Stuff stuff;
	Group group;

	Teacher& current;
};
#pragma once

#include "Group.h"
#include "Stuff.h"
#include "ui.h"
#include "utils.hpp"

class College
{
public:
	College() : menu(std::move(init()))
	{}

	void run();

private:
	auto init() -> Menu<Window<3UL>, Window<3UL>, Window<2UL>, Window<5UL>>;

	bool signInTeacher();
	bool signInStudent();

	bool selectGroup();
	void changePassword();

	void showMark(const Student& stud);

	Stuff stuff;
	Group group;

	Teacher* currTeacher { nullptr };
	Student* currStudent { nullptr };
	Menu<Window<3UL>, Window<3UL>, Window<2UL>, Window<5UL>> menu;
};
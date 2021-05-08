#pragma once

#include "Group.h"
#include "Stuff.h"
#include "ui.h"
#include "utils.hpp"

class College
{
public:
	static College &getInstance() {
		static College self;
		return self;
	}

	void run();

private:
	College() : menu(std::move(init())), currTeacher(nullptr), currStudent(nullptr)
	{}

	auto init() -> Menu<Window<3UL>, Window<3UL>, Window<2UL>, Window<5UL>>;

	bool signInTeacher();
	bool signInStudent();

	bool selectGroup();
	void changePassword();

	void quit();

	void showMark(const Student& stud);

	Stuff stuff;
	Group group;

	Teacher* currTeacher {};
	Student* currStudent {};
	Menu<Window<3UL>, Window<3UL>, Window<2UL>, Window<5UL>> menu;
};
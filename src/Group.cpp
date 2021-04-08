#include "Group.h"
#include <OpenXLSX.hpp>

Group::Group(int number) : number { number }
{}

void Group::addStudent(Student& stud)
{
	stud.setGroup(number);
	students.insert(stud);
}

bool Group::removeStudent(std::string_view name, std::string_view surname)
{
	Student toFind { name, surname, number };

	if (auto search = students.find(toFind); search != students.end())
	{
		students.erase(search);
		return true;
	}

	return false;
}

void Group::saveToExcel(std::string_view filename)
{
	using namespace OpenXLSX;
	XLDocument doc;

	doc.create("./Groups.xlsx");

	auto wks = doc.workbook().worksheet(std::to_string(number));

	wks.cell(XLCellReference("A1")).value() = "Surname";
	wks.cell(XLCellReference("B1")).value() = "Name";

	int number { 2 };
	for (auto& stud : students)
	{
		wks.cell(XLCellReference("A" + std::to_string(number))).value() = stud.getSurname();
		wks.cell(XLCellReference("B" + std::to_string(number))).value() = stud.getName();
	}

	doc.save();
}
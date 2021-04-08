#include "Group.h"
#include <OpenXLSX.hpp>

Group::Group(int number) : number { number }
{}

void Group::addStudent(const Student& stud)
{
	Student tmp = stud;
	tmp.setGroup(number);
	students.insert(tmp);
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

	doc.workbook().addWorksheet(std::to_string(number));
	doc.workbook().deleteSheet("Sheet1");
	auto wks = doc.workbook().worksheet(std::to_string(number));

	wks.cell(XLCellReference("A1")).value() = "Surname";
	wks.cell(XLCellReference("B1")).value() = "Name";

	int index { 2 };
	for (auto& stud : students)
	{
		wks.cell(XLCellReference("A" + std::to_string(index))).value() = stud.getSurname();
		wks.cell(XLCellReference("B" + std::to_string(index))).value() = stud.getName();
		index++;
	}

	doc.save();
}
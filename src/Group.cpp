#include "Group.h"
#include <OpenXLSX.hpp>
#include <filesystem>

Group::Group(int number) : number { number }
{}

void Group::addStudent(const Student& stud)
{
	Student tmp = stud;
	tmp.setGroup(number);
	students.insert(tmp);
	count++;
}

bool Group::removeStudent(std::string_view name, std::string_view surname)
{
	Student toFind { name, surname, number };

	if (auto search = students.find(toFind); search != students.end())
	{
		students.erase(search);
		count--;
		return true;
	}

	return false;
}

void Group::loadFromExcel(const std::string& filename, int number)
{
	using namespace OpenXLSX;
	XLDocument doc;

	this->number = number;

	doc.open(filename);
	auto wks = doc.workbook().worksheet(std::to_string(number));

	auto max = wks.rowCount() + 1;
	for (int index { 2 }; index < max; index++)
	{
		auto surname = wks.cell(XLCellReference("A" + std::to_string(index))).value();
		auto name = wks.cell(XLCellReference("B" + std::to_string(index))).value();
		this->addStudent(Student { name.get<std::string>(), surname.get<std::string>(), number });
	}

	doc.close();
}

void Group::saveToExcel(const std::string& filename)
{
	using namespace OpenXLSX;
	XLDocument doc;

	// Перевіряємо, чи існує файл. Якщо файл існує, то його не перестворюємо, а відкриваємо
	if (std::filesystem::exists(filename))
	{
		doc.open(filename);
	}
	else
	{
		doc.create(filename);
	}

	auto wbk = doc.workbook();

	// Перевіряємо, чи існує Аркуш з іменем групи, якщо не існує додаємо
	if (!wbk.worksheetExists(std::to_string(number)))
	{
		wbk.addWorksheet(std::to_string(number));
	}

	// clang-format off
	/* Maybe depracte in future */ if (wbk.worksheetExists("Sheet1")) { wbk.deleteSheet("Sheet1"); }
	// clang-format on

	auto wks = wbk.worksheet(std::to_string(number));

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
	doc.close();
}
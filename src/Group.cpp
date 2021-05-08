#include "Group.h"
#include "config.h"
#include "utils.hpp"
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

Student *Group::getStudent(std::string_view name, std::string_view surname) const
{
	Student toFind { name, surname, this->number };

	if (auto search = students.find(toFind); search != students.end())
	{
		return const_cast<Student*>(&(*search));
	}
	throw person_error { "not found student", __FILE__, __LINE__, __PRETTY_FUNCTION__, "no such student in set" };
}

void Group::loadFromExcel()
{
	clear();

	using namespace OpenXLSX;
	XLDocument doc;

	doc.open(std::to_string(number) + "Config::EXC_FILE");
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

void Group::loadSubject(const std::string& subject)
{
	using namespace OpenXLSX;
	XLDocument doc;
	doc.open(std::to_string(number) + "Config::EXC_FILE");

	auto wbk = doc.workbook();
	if (!wbk.worksheetExists(subject))
	{
		doc.close();
		return;
	}
	auto wks = wbk.worksheet(subject);
	auto row = wks.rowCount() + 1;
	auto col = wks.row(1).cellCount() + 1;
	int i = 2;
	for (auto& stud : students)
	{
		for (auto j { 3 }; j < col; j++)
		{
			auto val = wks.cell(XLCellReference(i, j)).value().get<int>();
			auto date = wks.cell(XLCellReference(1, j)).value().asString();
			tm tm;
			strptime(date.c_str(), "%d.%m.%Y", &tm);
			auto mark = (val != -1) ? std::optional<int> { val } : std::nullopt;
			stud.addMark(subject, Mark { mark, subject, tm });
		}
		i++;
	}

	doc.close();
}

void Group::saveToExcel()
{
	using namespace OpenXLSX;
	XLDocument doc;

	auto filename = (std::to_string(number) + "Config::EXC_FILE");
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

void Group::updateSubject(const std::string& subject)
{
	using namespace OpenXLSX;
	XLDocument doc;
	doc.open(std::to_string(number) + "Config::EXC_FILE");

	auto wbk = doc.workbook();
	/// Перевіряємо, чи існує Аркуш з предметом, якщо не існує клонуємо
	if (!wbk.worksheetExists(subject))
	{
		wbk.cloneSheet(std::to_string(number), subject);
	}

	auto wks = wbk.worksheet(subject);

	auto current_date = wks.row(1).cellCount() + 1;
	wks.cell(XLCellReference(1, current_date)).value() = students.begin()->getMark(subject).getDate();

	int index { 2 };
	for (auto& stud : students)
	{
		wks.cell(XLCellReference(index, current_date)).value() = stud.getMark(subject).value.value_or(-1);
		index++;
	}

	doc.save();
	doc.close();
}

int Group::getNumber() const
{
	return this->number;
}

void Group::clear()
{
	students.clear();
	number = 0;
	count = 0;
}
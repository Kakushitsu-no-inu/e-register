#include "group.h"
#include "mark.h"
#include "config.h"
#include "utils.hpp"
#include <OpenXLSX.hpp>
#include <filesystem>

group::group(int number) : number{number} {}

void group::add_student(const student &stud) {
  student tmp = stud;
  tmp.set_group(number);
  students.insert(tmp);
  count++;
}

bool group::remove_student(std::string_view name, std::string_view surname) {
  student toFind{name, surname, number};

  if (auto search = students.find(toFind); search != students.end()) {
    students.erase(search);
    count--;
    return true;
  }

  return false;
}

student *group::get_student(std::string_view name, std::string_view surname) const {
  auto search = std::find_if(students.begin(), students.end(), [&](const student &stud) {
    return stud.get_name() == name && stud.get_surname() == surname;
  });

  if (search != students.end()) {
    return const_cast<student *>(&(*search));
  }
  throw person_error{"not found student"};
}

void group::load_from_excel() {
  clear();

  using namespace OpenXLSX;
  XLDocument doc;

  doc.open(std::to_string(number) + config::EXC_FILE);
  auto wks = doc.workbook().worksheet(std::to_string(number));

  auto max = wks.rowCount() + 1;
  for (int index{2}; index < max; index++) {
    auto surname = wks.cell(XLCellReference("A" + std::to_string(index))).value();
    auto name    = wks.cell(XLCellReference("B" + std::to_string(index))).value();
    this->add_student(student{name.get<std::string>(), surname.get<std::string>(), number});
  }

  doc.close();
}

void group::load_subject(const std::string &subject) {
  using namespace OpenXLSX;
  XLDocument doc;
  doc.open(std::to_string(number) + config::EXC_FILE);

  auto wbk = doc.workbook();
  if (!wbk.worksheetExists(subject)) {
    doc.close();
    return;
  }

  auto wks = wbk.worksheet(subject);
  auto row = wks.rowCount() + 1;
  auto col = wks.row(1).cellCount() + 1;
  for (int i{2}; auto &stud : students) {
    for (auto j{3}; j < col; j++) {
      auto val  = wks.cell(XLCellReference(i, j)).value().asString();
      auto date = wks.cell(XLCellReference(1, j)).value().asString();
      tm   tm;
      strptime(date.c_str(), "%d.%m.%Y", &tm);
      stud.add_mark(subject, mark{val, subject, tm});
    }
    i++;
  }

  doc.close();
}

void group::save_to_excel() {
  using namespace OpenXLSX;
  XLDocument doc;

  auto filename = (std::to_string(number) + config::EXC_FILE);
  // Перевіряємо, чи існує файл. Якщо файл існує, то його не перестворюємо, а відкриваємо
  if (std::filesystem::exists(filename)) {
    doc.open(filename);
  } else {
    doc.create(filename);
  }

  auto wbk = doc.workbook();

  // Перевіряємо, чи існує Аркуш з іменем групи, якщо не існує додаємо
  if (!wbk.worksheetExists(std::to_string(number))) {
    wbk.addWorksheet(std::to_string(number));
  }

  // clang-format off
	/* Maybe deprecate in future */ 
  if (wbk.worksheetExists("Sheet1")) { wbk.deleteSheet("Sheet1"); }
  // clang-format on

  auto wks = wbk.worksheet(std::to_string(number));

  wks.cell(XLCellReference("A1")).value() = "Surname";
  wks.cell(XLCellReference("B1")).value() = "Name";

  for (int index{2}; auto &stud : students) {
    wks.cell(XLCellReference("A" + std::to_string(index))).value() = stud.get_surname();
    wks.cell(XLCellReference("B" + std::to_string(index))).value() = stud.get_name();
    index++;
  }

  doc.save();
  doc.close();
}

void group::update_subject(const std::string &subject) {
  using namespace OpenXLSX;
  XLDocument doc;
  doc.open(std::to_string(number) + config::EXC_FILE);

  auto wbk = doc.workbook();
  /// Перевіряємо, чи існує Аркуш з предметом, якщо не існує клонуємо
  if (!wbk.worksheetExists(subject)) {
    wbk.cloneSheet(std::to_string(number), subject);
  }

  auto wks = wbk.worksheet(subject);

  auto current_date = wks.row(1).cellCount() + 1;
  wks.cell(XLCellReference(1, current_date)).value() =
    students.begin()->get_last_mark(subject).time_to_string();

  for (int index{2}; auto &stud : students) {
    wks.cell(XLCellReference(index, current_date)).value() = stud.get_last_mark(subject).value;
    index++;
  }

  doc.save();
  doc.close();
}

int group::get_number() const { return this->number; }

void group::clear() {
  students.clear();
  number = 0;
  count  = 0;
}

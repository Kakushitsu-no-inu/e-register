#include "Stuff.h"
#include "config.h"
#include <algorithm>
#include <fstream>

void Stuff::saveToFile()
{
	std::ofstream file { config::STUFF_FILE, std::ios::out };
	if (file.good())
	{
		std::for_each(teachers.begin(), teachers.end(), [&file](const Teacher& teacher) {
			file << teacher.getSurname() << ' ' << teacher.getName() << ' ' << teacher.getSubject() << ' '
				 << teacher.getPassword() << '\n';
		});
	}

	file.close();
}

void Stuff::loadFromFile()
{
	std::ifstream file { config::STUFF_FILE, std::ios::in };
	if (!file.good())
	{
		throw std::runtime_error { "Can't open file!" };
	}

	std::string name {}, surname {}, subject {}, password {};
	while (file >> name >> surname >> subject >> password)
	{
		teachers.emplace_back(Teacher { name, surname, subject, password });
	}
	file.close();
}

void Stuff::addTeacher(const Teacher& newTeacher)
{
	teachers.emplace_back(newTeacher);
}

const Teacher& Stuff::getTeacher(std::string_view surname, std::string_view name) const
{
	if (auto find = std::find_if(teachers.begin(),
			teachers.end(),
			[&](const Teacher& teach) { return teach.getSurname() == surname && teach.getName() == name; });
		find != teachers.end())
	{
		return *find;
	}
	throw person_error { "not found teacher", __FILE__, __LINE__, __PRETTY_FUNCTION__, "no such teacher in set" };
}

Teacher* Stuff::signIn(const std::string& password)
{
	if (auto it = std::find_if(
			teachers.begin(), teachers.end(), [&](const Teacher& t) { return t.getPassword() == password; });
		it != teachers.end())
	{
		return &(*it);
	}
	throw person_error { "not found teacher", __FILE__, __LINE__, __PRETTY_FUNCTION__, "no such teacher in set" };
}

#include "Stuff.h"
#include "config.h"
#include <algorithm>
#include <fstream>

void Stuff::saveToFile()
{
	std::ofstream file { Config::STUFF_FILE, std::ios::out };
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
	std::ifstream file { Config::STUFF_FILE, std::ios::in };
	if (file.good())
	{
		std::string surname {}, name {}, subject {}, password {};
		while (file >> surname >> name >> subject >> password)
		{
			teachers.emplace_back(Teacher { surname, name, subject, password });
		}
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
			[&surname, &name](
				const Teacher& teach) { return teach.getSurname() == surname && teach.getName() == name; });
		find != teachers.end())
	{
		return *find;
	}
}
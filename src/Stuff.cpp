#include "Stuff.h"
#include "config.h"
#include <algorithm>
#include <fstream>

void Stuff::saveToFile()
{
	std::ofstream file { Config::STUFF_FILE, std::ios::out };
	if (file.good())
	{
		const auto write = [&file](const Teacher& teacher) {
			file << teacher.getSurname() << ' ' << teacher.getName() << teacher.getSubject() << '\n';
		};

		std::for_each(teachers.begin(), teachers.end(), write);
	}

	file.close();
}

void Stuff::loadFromFile()
{
	std::ifstream file { Config::STUFF_FILE, std::ios::in };
	if (file.good())
	{
		std::string surname {}, name {}, subject {};
		while (file >> surname >> name >> subject)
		{
			teachers.emplace_back(Teacher { surname, name, subject });
		}
	}

	file.close();
}

void Stuff::addTeacher(const Teacher& newTeacher)
{
	teachers.emplace_back(newTeacher);
}
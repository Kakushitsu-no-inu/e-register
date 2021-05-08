#include "Mark.h"
#include "Teacher.h"

Teacher::Teacher(std::string_view name, std::string_view surname) : Person(name, surname)
{}

Teacher::Teacher(std::string_view name, std::string_view surname, std::string_view subject) :
	Person(name, surname),
	subject(subject)
{}

Teacher::Teacher(std::string_view name, std::string_view surname, std::string_view subject, std::string password) :
	Person(name, surname),
	subject(subject),
	password(password)
{}

void Teacher::setPassword(std::string_view password)
{
	this->password = password;
}

const std::string& Teacher::getSubject() const
{
	return subject;
}

const std::string& Teacher::getPassword() const
{
	return password;
}

void Teacher::setMark(Student& stud, std::optional<int> value) const
{
	std::time_t now { std::time(nullptr) };
	std::tm* date { std::localtime(&now) };

	stud.addMark(this->subject, Mark { value, this->subject, *date });
}

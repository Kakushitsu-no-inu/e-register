#include <Teacher.h>

Teacher::Teacher(std::string_view name, std::string_view surname) : Person(name, surname)
{}

Teacher::Teacher(std::string_view name, std::string_view surname, std::string_view subject) :
	Person(name, surname),
	subject(subject)
{}

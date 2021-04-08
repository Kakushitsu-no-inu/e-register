#include "Person.h"

Person::Person(std::string_view name) : Person { name, "" }
{}

Person::Person(std::string_view name, std::string surname) : name { name } surname { surname }
{}
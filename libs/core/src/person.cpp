#include "person.h"

person::person(std::string_view name) : person{name, ""} {}

person::person(std::string_view name, std::string_view surname) : name{name}, surname{surname} {}

const std::string &person::get_name() const { return name; }

const std::string &person::get_surname() const { return surname; }

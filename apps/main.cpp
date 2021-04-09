#include "Stuff.h"
#include <iostream>

auto main() -> int
{
	Stuff clg {};

	clg.addTeacher(Teacher { "Lazoryk", "Vasyl", "OOP" , "qwerty123"});
	clg.addTeacher(Teacher { "Koropetskyi", "Vasyl", "WEB", "qwerty12" });

	clg.saveToFile();

	Stuff test {};
	test.loadFromFile();

	return 0;
}
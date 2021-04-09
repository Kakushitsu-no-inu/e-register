#include "Stuff.h"
#include <iostream>

auto main() -> int
{
	Stuff clg {};

	clg.addTeacher(Teacher { "Lazoryk", "Vasyl", "OOP" });
	clg.addTeacher(Teacher { "Koropetskyi", "Vasyl", "WEB" });

	clg.saveToFile();

	Stuff test {};
	test.loadFromFile();

	return 0;
}
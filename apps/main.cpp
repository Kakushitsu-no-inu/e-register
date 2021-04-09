#include "Stuff.h"
#include <iostream>

auto main() -> int
{
	Teacher a{"Lazoryk", "Vasyl", "OOP"};
	Student b{"Andrii","Liashenko",314};
	a.setMark(b,{3});
	return 0;
}
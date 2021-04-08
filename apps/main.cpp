#include <iostream>
#include "Group.h"

auto main() -> int
{
	Group KN_314 { 314 };
	Student a{"Andrii","Liashenko"};
	Student b{"Ivan","Tkachuk"};
	KN_314.addStudent(std::move(a));
	KN_314.addStudent(std::move(b));
	
}
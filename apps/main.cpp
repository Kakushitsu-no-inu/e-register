#include <iostream>
#include "Group.h"

auto main() -> int
{
	Group KN_314 { 314 };
	Student b{"Ivan","Tkachuk"};
	Student a{"Andrii","Liashenko"};
	KN_314.addStudent(b);
	KN_314.addStudent(a);

	// KN_314.saveToExcel("college.excel");
}
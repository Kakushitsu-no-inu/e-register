#include "college.h"

int main()
{
	auto clg = College::getInstance();
	try
	{
		clg.run();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}
	return 0;
}
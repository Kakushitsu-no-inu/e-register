#include "college.h"

int main()
{
	College clg;
	try {
		clg.run();
	} catch (std::exception &err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}
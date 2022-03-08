#include "ContainerTest.hpp"
#include "TestCase.hpp"
#include "../utility/log_formatting.hpp"
#include "../utility/Timer.hpp"
#include "../utility/print_color.hpp"
#include <iostream>

ContainerTest::ContainerTest(const std::string& type):
container_type(type) {}


void	ContainerTest::test(int category) {
	void (ContainerTest::*func_array[])() = {
		&ContainerTest::testConstructor,
		&ContainerTest::testIterator,
		&ContainerTest::testCapacity,
		&ContainerTest::testElementAccess,
		&ContainerTest::testModifiers,
		&ContainerTest::testAllocator,
		&ContainerTest::testOperator
	};
	utility::Timer	timer;
	if (category == 0) {
		for (int i = 0; i < ALL_CATEGORY; ++i) {
			logTitleCategory(container_type, getCategoryName(static_cast<CategoryType>(i)));
			(this->*func_array[i])(); // use of this->: A non-static member function pointer can't be called in the usual way. You've got to tell it which object to use.
		}
	}
	else {
		logTitleCategory(container_type, getCategoryName(static_cast<CategoryType>(category - 1)));
		(this->*func_array[category - 1])();
	}
	std::cout << BLUE_BOLD << "[ " << container_type << " ] running time is: " 
				<< WHITE_BOLD << timer.elapsed() << BLUE_BOLD << " seconds\n" << RESET_COLOR;
}

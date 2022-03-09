#include "TestCase.hpp"
#include "VectorTest.hpp"
#include "MapTest.hpp"
#include "StackTest.hpp"
#include "../utility/get_input.hpp"
#include "../utility/log_formatting.hpp"
#include "map_temp.hpp" //TODO: to delete when RBT is done

std::string	getContainerName(ContainerType container) {
	switch (container) {
		case VECTOR:
			return "vector";
		case MAP:
			return "map";
		case STACK:
			return "stack";
		default:
			return "All containers";
	}
}

std::string	getCategoryName(CategoryType category) {
	switch (category) {
		case CONSTRUCTOR:
			return "constructor";
		case ITERATOR:
			return "iterator";
		case CAPACITY:
			return "capacity";
		case ELEMENT_ACCESS:
			return "element_access";
		case MODIFIERS:
			return "modifiers";
		case ALLOCATOR:
			return "allocator";
		case OPERATOR:
			return "operator";
		default:
			return "All categories";
	}
}

void	displayContainer() {
	utility::printBlue("Available container type:");
	utility::printBlue("0. All");
	utility::printBlue("1. Vector");
	utility::printBlue("2. Map");
	utility::printBlue("3. Stack");
}

void	displayCategory() {
	utility::printBlue("Available test category type:");
	utility::printBlue("0. All");
	utility::printBlue("1. Constructor");
	utility::printBlue("2. Iterator");
	utility::printBlue("3. Capacity");
	utility::printBlue("4. Element_Access");
	utility::printBlue("5. Modifiers");
	utility::printBlue("6. Allocator");
	utility::printBlue("7. Operator");
}

static bool	checkContainerScope(const int& n) {
	return (n >= 0 && n <= 3);
}

static bool	checkCategoryScope(const int& n) {
	return (n >= 0 && n <= 7);
}

void	TestCase::testVector(int category) {
	VectorTest test;
	test.test(category);
}

void	TestCase::testMap(int category) {
	MapTest test;
	test.test(category);
}

void	TestCase::testStack(int category) {
	StackTest test;
	test.test(category);
}

void	TestCase::testContainer(int container, int category) {
	void (TestCase::*func_array[])(int) = {
		&TestCase::testVector,
		&TestCase::testMap,
		&TestCase::testStack
	};
	if (container == 0) {
		for (int i = 0; i < ALL_CONTAINER; ++i) {
			logTitleContainer(getContainerName(static_cast<ContainerType>(i)));
			(this->*func_array[i])(category);
		}
	}
	else {
		logTitleContainer(getContainerName(static_cast<ContainerType>(container - 1)));
		(this->*func_array[container - 1])(category);
	}
}

void	TestCase::run() {
	// TODO: to figure out a way to make the selection applicable for both ft.out & std.out
	// displayContainer();
	// int container = utility::getInput<int>("Choose container (index): ", checkContainerScope);
	// displayCategory();
	// int category = utility::getInput<int>("Choose test category (index): ", checkCategoryScope);
	// testContainer(container, category);

	// testContainer(0, 0);
	testMapTemp();

}

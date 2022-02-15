#include "test.hpp"
#include "../utility/get_input.hpp"
#include "../utility/log_formatting.hpp"

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

static void	testCategory(int category, void	(*func_array[])()) {
	if (category == 0) {
		for (int i = 0; i < ALL_CATEGORY; ++i) {
			logTitleCategory(getCategoryName(static_cast<CategoryType>(i)));
			(*func_array[i])();
		}
	}
	else {
		logTitleCategory(getCategoryName(static_cast<CategoryType>(category - 1)));
		(*func_array[category - 1])();
	}
}

static void	testVector(int category) {
	static void	(*func_array[])() = {vector::testConstructor, vector::testIterator, vector::testCapacity, vector::testElementAccess, vector::testModifiers, vector::testAllocator, vector::testOperator};
	testCategory(category, func_array);
}

static void	testMap(int category) {
	static void	(*func_array[])() = {map::testConstructor, map::testIterator, map::testCapacity, map::testElementAccess, map::testModifiers, map::testAllocator, map::testOperator};
	testCategory(category, func_array);
}

static void	testStack(int category) {
	static void	(*func_array[])() = {stack::testConstructor, stack::testIterator, stack::testCapacity, stack::testElementAccess, stack::testModifiers, stack::testAllocator, stack::testOperator};
	testCategory(category, func_array);
}

static void	testContainer(int container, int category) {
	static void (*func_array[])(int) = {testVector, testMap, testStack};
	if (container == 0) {
		for (int i = 0; i < ALL_CONTAINER; ++i) {
			logTitleContainer(getContainerName(static_cast<ContainerType>(i)));
			(*func_array[i])(category);
		}
	}
	else {
		logTitleContainer(getContainerName(static_cast<ContainerType>(container - 1)));
		(*func_array[container - 1])(category);
	}
}

void	TestCase::run() {
	// TODO: to figure out a way to make the selection applicable for both ft.out & std.out
	// displayContainer();
	// int container = utility::getInput<int>("Choose container (index): ", checkContainerScope);
	// displayCategory();
	// int category = utility::getInput<int>("Choose test category (index): ", checkCategoryScope);
	// testContainer(container, category);
	testContainer(0, 0);
}

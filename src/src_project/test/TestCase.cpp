#include "TestCase.hpp"
#include "VectorTest.hpp"
#include "MapTest.hpp"
#include "StackTest.hpp"
#include "SetTest.hpp"
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
		case SET:
			return "set";
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

void	TestCase::testSet(int category) {
	SetTest test;
	test.test(category);
}

void	TestCase::testContainer(int container, int category) {
	void (TestCase::*func_array[])(int) = {
		&TestCase::testVector,
		&TestCase::testMap,
		&TestCase::testStack,
		&TestCase::testSet
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
	testContainer(0, 0);
}

#pragma once
#include <string>

enum ContainerType {
	VECTOR,
	MAP,
	STACK,
	SET,
	ALL_CONTAINER
};

enum CategoryType {
	CONSTRUCTOR,
	ITERATOR,
	CAPACITY,
	ELEMENT_ACCESS,
	MODIFIERS,
	ALLOCATOR,
	OPERATOR,
	ALL_CATEGORY
};

std::string	getContainerName(ContainerType container);
std::string	getCategoryName(CategoryType category);

class TestCase {
	public:
		TestCase() {};
		~TestCase() {};

		void	run();
	private:
		TestCase(const TestCase& src) {};
		void	testContainer(int container, int category);
		void	testVector(int category);
		void	testMap(int category);
		void	testStack(int category);
		void	testSet(int category);
};

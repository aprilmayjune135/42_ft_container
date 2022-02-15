#pragma once
#include <string>

enum ContainerType {
	VECTOR,
	MAP,
	STACK,
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
};

namespace vector {
	void	testConstructor();
	void	testIterator();
	void	testCapacity();
	void	testElementAccess();
	void	testModifiers();
	void	testAllocator();
	void	testOperator();
}

namespace map {
	void	testConstructor();
	void	testIterator();
	void	testCapacity();
	void	testElementAccess();
	void	testModifiers();
	void	testAllocator();
	void	testOperator();
}

namespace stack {
	void	testConstructor();
	void	testIterator();
	void	testCapacity();
	void	testElementAccess();
	void	testModifiers();
	void	testAllocator();
	void	testOperator();
}


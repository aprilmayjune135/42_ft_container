#pragma once
#include <string>
#include <iostream> //TODO: delete

class TestCase {
	public:
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

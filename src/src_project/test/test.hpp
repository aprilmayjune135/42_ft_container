#pragma once
#include <string>

class TestCase {
	public:
		enum ContainerType {
			VECTOR,
			MAP,
			STACK
		};

		enum CategoryType {
			ALL,
			CONSTRUCTOR,
			ITERATOR,
			CAPACITY,
			ELEMENT_ACCESS,
			MODIFIERS,
			ALLOCATOR,
			OPERATOR
		};

		TestCase() {};
		~TestCase() {};

		void	init();

	private:
		ContainerType	container;
};

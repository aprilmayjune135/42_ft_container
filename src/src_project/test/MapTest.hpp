#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <map>
#else
	#include "../container/map.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"

class MapTest: public ContainerTest {
	public:
		// typedef ft::map<int>				t_int;
		// typedef ft::map<std::string>		t_str;
		// typedef ft::map<dummy_type>		t_dummy;
		// typedef ft::map<dummy_type_2D>	t_dummy_2D;

		MapTest();
		~MapTest() {};

		void	testConstructor();
		void	testIterator();
		void	testCapacity();
		void	testElementAccess();
		void	testModifiers();
		void	testAllocator();
		void	testOperator();
};

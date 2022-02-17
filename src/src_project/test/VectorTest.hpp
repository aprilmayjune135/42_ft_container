#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <vector>
#else
	#include "../container/vector.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"

template <class T>
class Source {
	public:
		Source(std::size_t n);
		~Source() {};
		std::string 	type;
		ft::vector<T>	data;
	private:
		Source() {};

};

class VectorTest: public ContainerTest {
	public:
		typedef ft::vector<int>				t_int;
		typedef ft::vector<std::string>		t_str;
		typedef ft::vector<dummy_type>		t_dummy;
		typedef ft::vector<dummy_type_2D>	t_dummy_2D;

		VectorTest();
		~VectorTest() {};

		void	testConstructor();
		void	testIterator();
		void	testCapacity();
		void	testElementAccess();
		void	testModifiers();
		void	testAllocator();
		void	testOperator();
};

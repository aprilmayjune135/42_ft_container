#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <vector>
#else
	#include "../container/vector.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"

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

		template <class T>
		void	testPerTypeConstructor(const Source< ft::vector<T> >& src);

		template <class T>
		void	testPerTypeIterator(Source< ft::vector<T> > src);

		template <class T>
		void	testPerTypeCapacity(const Source< ft::vector<T> >& src);

		template <class T>
		void	testPerTypeElementAccess(Source< ft::vector<T> > src);

		template <class T>
		void	testPerTypeModifiers(const Source< ft::vector<T> >& src);

		template <class T>
		void	testPerTypeOperator(const Source< ft::vector<T> >& src);


};

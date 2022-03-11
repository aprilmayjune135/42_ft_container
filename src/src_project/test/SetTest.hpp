#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <set>
#else
	#include "../container/set.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"


class SetTest: public ContainerTest {
	public:
		typedef int						t_value_int;
		typedef ft::set<int>			t_int;

		typedef std::string						t_value_str;
		typedef ft::set<std::string>			t_str;

		typedef dummy_type					t_value_dummy;
		typedef ft::set<dummy_type>			t_dummy;

		typedef dummy_type_2D					t_value_dummy_2D;
		typedef ft::set<dummy_type_2D>			t_dummy_2D;

		SetTest();
		~SetTest() {};

		void	testConstructor();
		void	testIterator();
		void	testCapacity();
		void	testElementAccess();
		void	testModifiers();
		void	testAllocator();
		void	testOperator();

		template<class T>
		void	testPerTypeConstructor(const Source< ft::set<T> >& src);

		template<class T>
		void	testPerTypeIterator(const Source< ft::set<T> >& src);

		template<class T>
		void	testPerTypeCapacity(const Source< ft::set<T> >& src);

		template<class T>
		void	testPerTypeElementAccess(const Source< ft::set<T> >& src);

		template<class T>
		void	testPerTypeModifiers(const Source< ft::set<T> >& src);

		template<class T>
		void	testPerTypeOperator(const Source< ft::set<T> >& src);

		void	testBound();

};

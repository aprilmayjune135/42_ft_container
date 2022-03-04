#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <map>
#else
	#include "../container/map.hpp"
	#include "../pair/pair.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"


class MapTest: public ContainerTest {
	public:
		typedef ft::pair<const int, char>	t_pair_int;
		typedef ft::map<int, char>			t_int;

		typedef ft::pair<const std::string, char>	t_pair_str;
		typedef ft::map<std::string, char>			t_str;

		typedef ft::pair<const dummy_type, char>	t_pair_dummy;
		typedef ft::map<dummy_type, char>			t_dummy;

		typedef ft::pair<const dummy_type_2D, char>	t_pair_dummy_2D;
		typedef ft::map<dummy_type_2D, char>			t_dummy_2D;

		MapTest();
		~MapTest() {};

		void	testConstructor();
		void	testIterator();
		void	testCapacity();
		void	testElementAccess();
		void	testModifiers();
		void	testAllocator();
		void	testOperator();

		template<class Key, class T>
		void	testPerTypeIterator(Source< ft::map<Key, T> > src);

		template<class Key, class T>
		void	testPerTypeCapacity(const Source< ft::map<Key, T> >& src);

		template<class Key, class T>
		void	testPerTypeElementAccess(Source< ft::map<Key, T> > src);

};

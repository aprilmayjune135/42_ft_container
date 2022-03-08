#pragma once
#include "ContainerTest.hpp"
#ifdef STANDARD
	#include <stack>
#else
	#include "../container/stack.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"
#include <vector>
#include <list>
#include <deque>

template <class T>
class StackSource {
	public:
		typedef typename ft::vector<T>	vector_ft_type;
		typedef typename std::vector<T>	vector_std_type;
		typedef typename std::list<T>	list_type;
		typedef typename std::deque<T>	deque_type;

		std::string 	type;
		StackSource(std::size_t n);

		vector_ft_type	vector_ft;
		vector_std_type	vector_std;
		list_type		list;
		deque_type		deque;

	private:
		StackSource();
};

class StackTest: public ContainerTest {
	public:
		typedef int				t_int;
		typedef std::string		t_str;
		typedef Dummy<int>		t_dummy;
		typedef Dummy<t_dummy>	t_dummy_2D;

		StackTest();
		~StackTest() {};

		void	testConstructor();
		void	testIterator();
		void	testCapacity();
		void	testElementAccess();
		void	testModifiers();
		void	testAllocator();
		void	testOperator();

		template <class T>
		void	testPerTypeConstructor(const StackSource<T>& src);

		template <class T>
		void	testPerTypeIterator(StackSource<T> src);

		template <class T>
		void	testPerTypeCapacity(const StackSource<T>& src);

		template <class T>
		void	testPerTypeElementAccess(StackSource<T> src);

		template <class T>
		void	testPerTypeModifiers(const StackSource<T>& src);

		template <class T>
		void	testPerTypeOperator(const StackSource<T>& src);


};

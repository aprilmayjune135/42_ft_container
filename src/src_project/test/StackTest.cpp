#include "StackTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				StackSource Constructor			**/ 
/*********************************************/

template<>
StackSource<StackTest::t_int>::StackSource(std::size_t n): type("int") {
	for (std::size_t i = 0; i < n; ++i) {
		vector_ft.push_back(i);
		vector_std.push_back(i);
		list.push_back(i);
		deque.push_back(i);
	}
}

template<>
StackSource<StackTest::t_str>::StackSource(std::size_t n): type("string") {
	static std::string	strings[10] = { "hello", "how", "are", "you", "doing", "today", "?", "I", "feel", "great!" };
	for (std::size_t i = 0; i < n; ++i) {
		std::size_t	j = i;
		j = j % 10;
		vector_ft.push_back(strings[j]);
		vector_std.push_back(strings[j]);
		list.push_back(strings[j]);
		deque.push_back(strings[j]);
	}
}

template<>
StackSource<StackTest::t_dummy>::StackSource(std::size_t n): type("dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i * 10);
		vector_ft.push_back(d);
		vector_std.push_back(d);
		list.push_back(d);
		deque.push_back(d);
	}
}

template<>
StackSource<StackTest::t_dummy_2D>::StackSource(std::size_t n): type("2D dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i * -3);
		dummy_type_2D d_2D(d);
		vector_ft.push_back(d_2D);
		vector_std.push_back(d_2D);
		list.push_back(d_2D);
		deque.push_back(d_2D);
	}
}

StackTest::StackTest(): ContainerTest("stack") {}

/*********************************************/ 
/**				constructor					**/ 
/*********************************************/

template <class T>
void	StackTest::testPerTypeConstructor(const StackSource<T>& src) {
	typedef ft::stack< T, typename StackSource<T>::vector_ft_type >		t_vector_ft;
	typedef ft::stack< T, typename StackSource<T>::vector_std_type >	t_vector_std;
	typedef ft::stack< T, typename StackSource<T>::list_type >			t_list;
	typedef ft::stack< T, typename StackSource<T>::deque_type >			t_deque;
	t_vector_ft		stack_vector_ft(src.vector_ft);
	t_vector_std	stack_vector_std(src.vector_std);
	t_list			stack_list(src.list);
	t_deque			stack_deque(src.deque);
	
	logTitleSection(src.type);
	printStack(stack_vector_ft);
	printStack(stack_vector_std);
	printStack(stack_list);
	printStack(stack_deque);
}

void	StackTest::testConstructor() {
	testPerTypeConstructor(StackSource<t_int>(100));
	testPerTypeConstructor(StackSource<t_str>(42));
	testPerTypeConstructor(StackSource<t_dummy>(50));
	testPerTypeConstructor(StackSource<t_dummy_2D>(99));
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/
void	StackTest::testIterator() {}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/
template <class C>
void	popElements(int n, C& stack) {
	while (!stack.empty() && n > 0) {
		stack.pop();
		--n;
	} 
}

template <class T>
void	StackTest::testPerTypeCapacity(const StackSource<T>& src) {
	typedef ft::stack< T, typename StackSource<T>::vector_ft_type >		t_vector_ft;
	typedef ft::stack< T, typename StackSource<T>::vector_std_type >	t_vector_std;
	typedef ft::stack< T, typename StackSource<T>::list_type >			t_list;
	typedef ft::stack< T, typename StackSource<T>::deque_type >			t_deque;
	t_vector_ft		stack_vector_ft(src.vector_ft);
	t_vector_std	stack_vector_std(src.vector_std);
	t_list			stack_list(src.list);
	t_deque			stack_deque(src.deque);
	
	logTitleSection(src.type);
	// print current size
	PRINT << stack_vector_ft.size() << ' ' << stack_vector_ft.empty() << ' ';
	PRINT << stack_vector_std.size() << ' ' << stack_vector_std.empty() << ' ';
	PRINT << stack_list.size() << ' ' << stack_list.empty() << ' ';
	PRINT << stack_deque.size() << ' ' << stack_deque.empty() << ' ';
	PRINT <<'\n';

	// pop half of the elements
	popElements(stack_vector_ft.size() / 2, stack_vector_ft);
	popElements(stack_vector_std.size() / 2, stack_vector_std);
	popElements(stack_list.size() / 2, stack_list);
	popElements(stack_deque.size() / 2, stack_deque);

	// print final size
	PRINT << stack_vector_ft.size() << ' ' << stack_vector_ft.empty() << ' ';
	PRINT << stack_vector_std.size() << ' ' << stack_vector_std.empty() << ' ';
	PRINT << stack_list.size() << ' ' << stack_list.empty() << ' ';
	PRINT << stack_deque.size() << ' ' << stack_deque.empty() << ' ';
	PRINT <<'\n';
}

void	StackTest::testCapacity() {
	testPerTypeCapacity(StackSource<t_int>(42));
	testPerTypeCapacity(StackSource<t_str>(20));
	testPerTypeCapacity(StackSource<t_dummy>(30));
	testPerTypeCapacity(StackSource<t_dummy_2D>(15));
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
void	StackTest::testElementAccess() {}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/
template <class T>
void	StackTest::testPerTypeModifiers(const StackSource<T>& src) {
	typedef ft::stack< T, typename StackSource<T>::vector_ft_type >		t_vector_ft;
	typedef ft::stack< T, typename StackSource<T>::vector_std_type >	t_vector_std;
	typedef ft::stack< T, typename StackSource<T>::list_type >			t_list;
	typedef ft::stack< T, typename StackSource<T>::deque_type >			t_deque;
	t_vector_ft		stack_vector_ft(src.vector_ft);
	t_vector_std	stack_vector_std(src.vector_std);
	t_list			stack_list(src.list);
	t_deque			stack_deque(src.deque);
	
	logTitleSection(src.type);
	for (std::size_t i = 0; i < src.vector_ft.size(); ++i) {
		stack_vector_ft.push(src.vector_ft[i]);
	}
	printStack(stack_vector_ft); // printStack() incl. top() and pop() for every element.
	for (std::size_t i = 0; i < src.vector_std.size(); ++i) {
		stack_vector_std.push(src.vector_std[i]);
	}
	printStack(stack_vector_std);
	for (typename StackSource<T>::list_type::const_iterator it = src.list.begin(); it != src.list.end(); ++it) {
		stack_list.push(*it);
	}
	printStack(stack_list);
	for (std::size_t i = 0; i < src.deque.size(); ++i) {
		stack_deque.push(src.deque[i]);
	}
	printStack(stack_deque);
}

void	StackTest::testModifiers() {
	testPerTypeModifiers(StackSource<t_int>(42));
	testPerTypeModifiers(StackSource<t_str>(20));
	testPerTypeModifiers(StackSource<t_dummy>(30));
	testPerTypeModifiers(StackSource<t_dummy_2D>(15));
}

/*********************************************/ 
/**				operator					**/ 
/*********************************************/
template <class T>
void	StackTest::testPerTypeOperator(const StackSource<T>& src) {
	typedef ft::stack< T, typename StackSource<T>::vector_ft_type >		t_vector_ft;
	typedef ft::stack< T, typename StackSource<T>::vector_std_type >	t_vector_std;
	typedef ft::stack< T, typename StackSource<T>::list_type >			t_list;
	typedef ft::stack< T, typename StackSource<T>::deque_type >			t_deque;
	t_vector_ft		stack_vector_ft(src.vector_ft);
	t_vector_std	stack_vector_std(src.vector_std);
	t_list			stack_list(src.list);
	t_deque			stack_deque(src.deque);
	t_vector_ft		stack_vector_ft_less(src.vector_ft);
	t_vector_std	stack_vector_std_less(src.vector_std);
	t_list			stack_list_less(src.list);
	t_deque			stack_deque_less(src.deque);
	t_vector_ft		stack_vector_ft_more(src.vector_ft);
	t_vector_std	stack_vector_std_more(src.vector_std);
	t_list			stack_list_more(src.list);
	t_deque			stack_deque_more(src.deque);
	stack_vector_ft_less.pop();
	stack_vector_std_less.pop();
	stack_list_less.pop();
	stack_deque_less.pop();
	stack_vector_ft_more.push(stack_vector_ft_more.top());
	stack_vector_std_more.push(stack_vector_std_more.top());
	stack_list_more.push(stack_list_more.top());
	stack_deque_more.push(stack_deque_more.top());

	logTitleSection(src.type);
	PRINT << (stack_vector_ft == stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft == stack_vector_ft_more) << ' ';
	PRINT << (stack_vector_ft != stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft != stack_vector_ft_more) << ' ';
	PRINT << (stack_vector_ft < stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft < stack_vector_ft_more) << ' ';
	PRINT << (stack_vector_ft <= stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft <= stack_vector_ft_more) << ' ';
	PRINT << (stack_vector_ft > stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft > stack_vector_ft_more) << ' ';
	PRINT << (stack_vector_ft >= stack_vector_ft_less) << ' ';
	PRINT << (stack_vector_ft >= stack_vector_ft_more) << ' ';
	PRINT << '\n';
	PRINT << (stack_vector_std == stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std == stack_vector_std_more) << ' ';
	PRINT << (stack_vector_std != stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std != stack_vector_std_more) << ' ';
	PRINT << (stack_vector_std < stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std < stack_vector_std_more) << ' ';
	PRINT << (stack_vector_std <= stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std <= stack_vector_std_more) << ' ';
	PRINT << (stack_vector_std > stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std > stack_vector_std_more) << ' ';
	PRINT << (stack_vector_std >= stack_vector_std_less) << ' ';
	PRINT << (stack_vector_std >= stack_vector_std_more) << ' ';
	PRINT << '\n';
	PRINT << (stack_list == stack_list_less) << ' ';
	PRINT << (stack_list == stack_list_more) << ' ';
	PRINT << (stack_list != stack_list_less) << ' ';
	PRINT << (stack_list != stack_list_more) << ' ';
	PRINT << (stack_list < stack_list_less) << ' ';
	PRINT << (stack_list < stack_list_more) << ' ';
	PRINT << (stack_list <= stack_list_less) << ' ';
	PRINT << (stack_list <= stack_list_more) << ' ';
	PRINT << (stack_list > stack_list_less) << ' ';
	PRINT << (stack_list > stack_list_more) << ' ';
	PRINT << (stack_list >= stack_list_less) << ' ';
	PRINT << (stack_list >= stack_list_more) << ' ';
	PRINT << '\n';
	PRINT << (stack_deque == stack_deque_less) << ' ';
	PRINT << (stack_deque == stack_deque_more) << ' ';
	PRINT << (stack_deque != stack_deque_less) << ' ';
	PRINT << (stack_deque != stack_deque_more) << ' ';
	PRINT << (stack_deque < stack_deque_less) << ' ';
	PRINT << (stack_deque < stack_deque_more) << ' ';
	PRINT << (stack_deque <= stack_deque_less) << ' ';
	PRINT << (stack_deque <= stack_deque_more) << ' ';
	PRINT << (stack_deque > stack_deque_less) << ' ';
	PRINT << (stack_deque > stack_deque_more) << ' ';
	PRINT << (stack_deque >= stack_deque_less) << ' ';
	PRINT << (stack_deque >= stack_deque_more) << ' ';
	PRINT << '\n';
}

void	StackTest::testOperator() {
	testPerTypeOperator(StackSource<t_int>(42));
	testPerTypeOperator(StackSource<t_str>(20));
	testPerTypeOperator(StackSource<t_dummy>(30));
	testPerTypeOperator(StackSource<t_dummy_2D>(15));
}


/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	StackTest::testAllocator() {}

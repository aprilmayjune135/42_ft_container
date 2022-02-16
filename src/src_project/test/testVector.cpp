#include "test.hpp"

#ifdef STANDARD
	#include <vector>
#else
	#include "../container/vector.hpp"
#endif

#include "Dummy.hpp"
#include "../utility/namespace.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"


namespace vector {
typedef	Dummy<std::string>		t_dummy;
typedef	Dummy<t_dummy>			t_dummy_2;


/*********************************************/ 
/**				constructor					**/ 
/*********************************************/
template <class T>
void	testPerTypeConstructor(const std::string& type, const T& src, int n = 100) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(type);
	
	logTitleSubSection("empty constructor");
	t_vector	v_empty;
	printVector(v_empty);
	logTitleSubSection("range constructor");
	t_vector	v_fill(n, src);
	printVector(v_fill);
	logTitleSubSection("fill constructor");
	t_vector	v_range(v_fill.begin(), v_fill.end() - n / 2);
	printVector(v_range);
	logTitleSubSection("copy constructor");
	t_vector	v_copy(v_range);
	printVector(v_copy);
	logTitleSubSection("operator= ");
	t_vector	v_equal = v_fill;
	printVector(v_equal);
	v_equal = v_range;
	printVector(v_equal);
}

void	testConstructor() {
	testPerTypeConstructor<int>("int", 42, 200);
	testPerTypeConstructor<double>("double", 87.65, 168);
	testPerTypeConstructor<std::string>("string", "hello", 50);
	t_dummy	dummy("world");
	t_dummy_2 dummy_2(dummy);
	testPerTypeConstructor<t_dummy>("dummy class", dummy, 150);
	testPerTypeConstructor<t_dummy_2>("dummy inception class", dummy_2, 10);
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/
void	testIterator() {
	typedef ft::vector<int>		t_vector;
	t_vector	v;
	for (std::size_t i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	logTitleSubSection("iterator");
	for (t_vector::iterator it = v.begin(); it != v.end(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("const iterator");
	for (t_vector::const_iterator it = v.begin(); it != v.end(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("reverse iterator");
	for (t_vector::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("const reverse iterator");
	for (t_vector::const_reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';

}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/
template <class T>
void	testPerTypeCapacity(const std::string& type, const T&src1, const T&src2, int n = 100) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(type);

	std::size_t	array[] = {n / 2, n + 1, n + 2, n * 2, n * 5};
	std::size_t	count = sizeof(array) / sizeof(std::size_t);
	logTitleSubSection("resize");
	t_vector	v1(n, src1);
	for (std::size_t i = 0; i < count; ++i) {
		v1.resize(array[i], src2);
		printVector(v1);
	}

	logTitleSubSection("empty");
	PRINT << v1.empty() << '\n';
	v1.resize(0);
	PRINT << v1.empty() << '\n';

	logTitleSubSection("reserve");
	t_vector	v2(n, src1);
	for (std::size_t i = 0; i < count; ++i) {
		v2.reserve(array[i]);
		printVector(v2);
	}
}

void	testCapacity() {
	testPerTypeCapacity<int>("int", 42, -77, 200);
	testPerTypeCapacity<double>("double", 87.65, 12.34, 168);
	testPerTypeCapacity<std::string>("string", "hello", "kitty!", 50);
	t_dummy	dummy1("magic");
	t_dummy	dummy2("world");
	testPerTypeCapacity<t_dummy>("dummy class", dummy1, dummy2, 150);
	t_dummy_2 dummy1_2(dummy1);
	t_dummy_2 dummy2_2(dummy2);
	testPerTypeCapacity<t_dummy_2>("dummy inception class", dummy1_2, dummy2_2, 10);
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
void	testElementAccess() {
	typedef ft::vector<int>		t_vector;
	t_vector	v;
	for (std::size_t i = 0; i < 10; ++i) {
		v.push_back(i * 10);
	}
	for (std::size_t i = 0; i < v.size() / 2; ++i) {
		v[i] += 1;
	}
	for (std::size_t i = v.size() / 2; i < v.size(); ++i) {
		v.at(i) -= 1;
	}
	v.front() = 123;
	v.back() = 987;
	printVector(v);
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/
void	testModifiers() {
}

/*********************************************/ 
/**				allocator					**/ 
/*********************************************/
void	testAllocator() {
}

/*********************************************/ 
/**				operator					**/ 
/*********************************************/
void	testOperator() {
}

} /* end of namespace vector */

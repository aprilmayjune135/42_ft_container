#include "VectorTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				Source Constructor			**/ 
/*********************************************/

template<>
Source<VectorTest::t_int>::Source(std::size_t n): type("int") {
	for (std::size_t i = 0; i < n; ++i) {
		data.push_back(i);
	}
}

template<>
Source<VectorTest::t_str>::Source(std::size_t n): type("string") {
	static std::string	strings[10] = { "hello", "how", "are", "you", "doing", "today", "?", "I", "feel", "great!" };
	for (std::size_t i = 0; i < n; ++i) {
		std::size_t	j = i;
		while (j > 9) {
			j -= 10;
		}
		data.push_back(strings[j]);
	}
}

template<>
Source<VectorTest::t_dummy>::Source(std::size_t n): type("dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i * 10);
		data.push_back(d);
	}
}

template<>
Source<VectorTest::t_dummy_2D>::Source(std::size_t n): type("2D dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i * -3);
		dummy_type_2D d_2D(d);
		data.push_back(d_2D);
	}
}

VectorTest::VectorTest(): ContainerTest("vector") {}

/*********************************************/ 
/**				constructor					**/ 
/*********************************************/

template <class T>
void	VectorTest::testPerTypeConstructor(const Source< ft::vector<T> >& src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);
	
	logTitleSubSection("empty constructor");
	t_vector	v_empty;
	printVector(v_empty);
	logTitleSubSection("fill constructor");
	t_vector	v_fill(src.data.size(), src.data.back());
	printVector(v_fill);
	logTitleSubSection("range constructor");
	t_vector	v_range(src.data.begin(), src.data.end());
	printVector(v_range);
	logTitleSubSection("copy constructor");
	t_vector	v_copy(src.data);
	printVector(v_copy);
	logTitleSubSection("operator= ");
	t_vector	v_equal = src.data;
	printVector(v_equal);
	v_equal = v_empty;
	printVector(v_equal);
}

void	VectorTest::testConstructor() {
	testPerTypeConstructor(Source<t_int>(42));
	testPerTypeConstructor(Source<t_str>(20));
	testPerTypeConstructor(Source<t_dummy>(30));
	testPerTypeConstructor(Source<t_dummy_2D>(15));
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/
template <class T>
void	VectorTest::testPerTypeIterator(Source< ft::vector<T> > src) {
	typedef ft::vector<T>	t_vector;
	logTitleSection(src.type);

	logTitleSubSection("iterator");
	for (typename t_vector::iterator it = src.data.begin(); it != src.data.end(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("const iterator");
	for (typename t_vector::const_iterator it = src.data.begin(); it != src.data.end(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("reverse iterator");
	for (typename t_vector::reverse_iterator it = src.data.rbegin(); it != src.data.rend(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	logTitleSubSection("const reverse iterator");
	for (typename t_vector::const_reverse_iterator it = src.data.rbegin(); it != src.data.rend(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
	

}

void	VectorTest::testIterator() {
	testPerTypeIterator(Source<t_int>(42));
	testPerTypeIterator(Source<t_str>(20));
	testPerTypeIterator(Source<t_dummy>(30));
	testPerTypeIterator(Source<t_dummy_2D>(15));
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/
template <class T>
void	VectorTest::testPerTypeCapacity(const Source< ft::vector<T> >& src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

	std::size_t	n = src.data.size();
	std::size_t	array[] = {1, n / 2, n + 1, n + 2, n * 2, n * 5};
	std::size_t	count = sizeof(array) / sizeof(std::size_t);

	logTitleSubSection("resize");
	t_vector	v1(src.data);
	for (std::size_t i = 0; i < count; ++i) {
		v1.resize(array[i], src.data.front());
		printVector(v1);
	}

	logTitleSubSection("empty");
	PRINT << v1.empty() << '\n';
	v1.resize(0);
	PRINT << v1.empty() << '\n';

	logTitleSubSection("reserve");
	t_vector	v2(src.data);
	for (std::size_t i = 0; i < count; ++i) {
		v2.reserve(array[i]);
		printVector(v2);
	}
}

void	VectorTest::testCapacity() {
	testPerTypeCapacity(Source<t_int>(42));
	testPerTypeCapacity(Source<t_str>(20));
	testPerTypeCapacity(Source<t_dummy>(30));
	testPerTypeCapacity(Source<t_dummy_2D>(15));
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
template <class T>
void	VectorTest::testPerTypeElementAccess(Source< ft::vector<T> > src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

	logTitleSubSection("front/back");
	T	temp = src.data.front();
	src.data.front() = src.data.back();
	src.data.back() = temp;
	PRINT << src.data.front() << '\n';
	PRINT << src.data.back() << '\n';

	logTitleSubSection("operator[]");
	for (std::size_t i = 0; i < src.data.size() - 1; ++i) {
		src.data[i] = src.data[i + 1];
	}
	printVector(src.data);

	logTitleSubSection("at");
	for (std::size_t i = 0; i < src.data.size() - 1; ++i) {
		src.data.at(i) = src.data.at(i + 1);
	}
	printVector(src.data);

}

void	VectorTest::testElementAccess() {
	testPerTypeElementAccess(Source<t_int>(42));
	testPerTypeElementAccess(Source<t_str>(20));
	testPerTypeElementAccess(Source<t_dummy>(30));
	testPerTypeElementAccess(Source<t_dummy_2D>(15));
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/
template <class T>
void	VectorTest::testPerTypeModifiers(const Source< ft::vector<T> >& src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

	std::size_t	n = src.data.size();
	std::size_t	array[] = {1, n / 2, n + 1, n + 2, n * 2, n * 5};
	std::size_t	count = sizeof(array) / sizeof(std::size_t);

	logTitleSubSection("assign - fill");
	t_vector	v_assign;
	for (std::size_t i = 0; i < count; ++i) {
		v_assign.assign(i, src.data.front());
		printVector(v_assign);
	}

	logTitleSubSection("assign - range");
	v_assign.assign(src.data.begin(), src.data.end());
	printVector(v_assign);

	logTitleSubSection("push_back");
	t_vector	v_push;
	for (std::size_t i = 0; i < n; ++i) {
		v_push.push_back(src.data[i]);
		printVectorCapacity(v_push);
	}
	printVector(v_push);

	logTitleSubSection("pop_back");
	v_push.pop_back();
	printVector(v_push);

	logTitleSubSection("insert - single");
	t_vector v_insert;
	for (std::size_t i = 0; i < n; ++i) {
		PRINT << *v_insert.insert(v_insert.begin(), src.data[i]) << " ";
		printVectorCapacity(v_insert);
	}
	printVector(v_insert);

	logTitleSubSection("erase - single");
	for (std::size_t i = 0; i < n; ++i) {
		PRINT << *v_insert.erase(v_insert.begin()) << " ";
	}
	printVector(v_insert);

	logTitleSubSection("insert - fill");
	for (std::size_t i = 0; i < count; ++i) {
		v_insert.insert(v_insert.end(), i, src.data.front());
		printVector(v_insert);
	}

	logTitleSubSection("clear");
	v_insert.clear();
	printVector(v_insert);

	logTitleSubSection("insert - range");
	v_insert.insert(v_insert.begin(), src.data.begin(), src.data.end());
	v_insert.insert(v_insert.end(), src.data.begin(), src.data.end());
	printVector(v_insert);

	logTitleSubSection("erase - range");
	PRINT << *v_insert.erase(v_insert.begin() + 1, v_insert.end() - 1) << " ";
	printVector(v_insert);

	logTitleSubSection("swap");
	t_vector v_empty;
	v_empty.swap(v_assign);
	printVector(v_empty);
	printVector(v_assign);

	logTitleSubSection("swap - non-member overload");
	swap(v_push, v_insert);
	printVector(v_push);
	printVector(v_insert);

}

void	VectorTest::testModifiers() {
	testPerTypeModifiers(Source<t_int>(42));
	testPerTypeModifiers(Source<t_str>(20));
	testPerTypeModifiers(Source<t_dummy>(30));
	testPerTypeModifiers(Source<t_dummy_2D>(15));
}


/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	VectorTest::testAllocator() {
	// TODO
}


/*********************************************/ 
/**				operator					**/ 
/*********************************************/
template <class T>
void	VectorTest::testPerTypeOperator(const Source< ft::vector<T> >& src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

	t_vector v = src.data;
	v.push_back(src.data.front());
	PRINT <<  (v == src.data) << " ";
	PRINT <<  (v != src.data) << " ";
	PRINT <<  (v < src.data) << " ";
	PRINT <<  (v <= src.data) << " ";
	PRINT <<  (v > src.data) << " ";
	PRINT <<  (v >= src.data) << " ";
	PRINT << '\n';
}

void	VectorTest::testOperator() {
	testPerTypeOperator(Source<t_int>(42));
	testPerTypeOperator(Source<t_str>(20));
	testPerTypeOperator(Source<t_dummy>(30));
	testPerTypeOperator(Source<t_dummy_2D>(15));
}


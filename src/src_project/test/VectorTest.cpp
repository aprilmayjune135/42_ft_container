#include "VectorTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				Source Constructor			**/ 
/*********************************************/

template<>
Source<int>::Source(std::size_t n): type("int") {
	for (std::size_t i = 0; i < n; ++i) {
		data.push_back(i);
	}
}

template<>
Source<std::string>::Source(std::size_t n): type("string") {
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
Source<dummy_type>::Source(std::size_t n): type("dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i * 10);
		data.push_back(d);
	}
}

template<>
Source<dummy_type_2D>::Source(std::size_t n): type("2D dummy class") {
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
void	testPerTypeConstructor(const Source<T>& src) {
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
	testPerTypeConstructor(Source<int>(42));
	testPerTypeConstructor(Source<std::string>(20));
	testPerTypeConstructor(Source<dummy_type>(30));
	testPerTypeConstructor(Source<dummy_type_2D>(15));
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/
template <class T>
void	testPerTypeIterator(Source<T> src) {
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
	testPerTypeIterator(Source<int>(42));
	testPerTypeIterator(Source<std::string>(20));
	testPerTypeIterator(Source<dummy_type>(30));
	testPerTypeIterator(Source<dummy_type_2D>(15));
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/
template <class T>
void	testPerTypeCapacity(const Source<T>& src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

	std::size_t	n = src.data.size();
	std::size_t	array[] = {n / 2, n + 1, n + 2, n * 2, n * 5};
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
	testPerTypeCapacity(Source<int>(42));
	testPerTypeCapacity(Source<std::string>(20));
	testPerTypeCapacity(Source<dummy_type>(30));
	testPerTypeCapacity(Source<dummy_type_2D>(15));
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
template <class T>
void	testPerTypeElementAccess(Source<T> src) {
	typedef ft::vector<T>		t_vector;
	logTitleSection(src.type);

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

	logTitleSubSection("front/back");
	T	temp = src.data.front();
	src.data.front() = src.data.back();
	src.data.back() = temp;
	PRINT << src.data.front();
	PRINT << src.data.back();

}

void	VectorTest::testElementAccess() {
	testPerTypeElementAccess(Source<int>(42));
	testPerTypeElementAccess(Source<std::string>(20));
	testPerTypeElementAccess(Source<dummy_type>(30));
	testPerTypeElementAccess(Source<dummy_type_2D>(15));
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/

void	VectorTest::testModifiers() {
	PRINT << "modifier" << '\n';
}


/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	VectorTest::testAllocator() {
	PRINT << "allocator" << '\n';
}


/*********************************************/ 
/**				operator					**/ 
/*********************************************/

void	VectorTest::testOperator() {
	PRINT << "operator" << '\n';
}


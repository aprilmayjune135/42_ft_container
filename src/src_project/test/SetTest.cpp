#include "SetTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				Source Constructor			**/ 
/*********************************************/

template<>
Source<SetTest::t_int>::Source(std::size_t n): type("int") {
	for (std::size_t i = 0; i < n; ++i) {
		SetTest::t_value_int	value(i);
		data.insert(value);
	}
}

template<>
Source<SetTest::t_str>::Source(std::size_t n): type("string") {
	static std::string	strings[10] = { "hello", "how", "are", "you", "doing", "today", "?", "I", "feel", "great!" };
	srand(time(NULL));
	for (std::size_t i = 0; i < n; ++i) {
		SetTest::t_value_str	value(strings[i % 10]);
		data.insert(value);
	}
}

template<>
Source<SetTest::t_dummy>::Source(std::size_t n): type("dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i);
		SetTest::t_value_dummy	value(d);
		data.insert(value);
	}
}

template<>
Source<SetTest::t_dummy_2D>::Source(std::size_t n): type("2D dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i);
		dummy_type_2D d_2D(d);
		SetTest::t_value_dummy_2D	value(d_2D);
		data.insert(value);
	}
}

SetTest::SetTest(): ContainerTest("set") {}

/*********************************************/ 
/**				constructor					**/ 
/*********************************************/

template<class T>
void	SetTest::testPerTypeConstructor(const Source< ft::set<T> >& src) {
	typedef	ft::set<T>	t_set;
	logTitleSection(src.type);

	logTitleSubSection("Constructor - default");
	t_set	set_default;
	printSet(set_default);

	logTitleSubSection("Constructor - range");
	t_set	set_range(src.data.begin(), src.data.end());
	printSet(set_range);
	set_range = set_default;
	printSet(set_range);

	logTitleSubSection("Constructor - copy");
	t_set	set_copy(src.data);
	printSet(set_copy);
	set_copy = set_default;
	printSet(set_copy);

	logTitleSubSection("Constructor - operator=");
	t_set	set_assign = src.data;
	printSet(set_assign);
}

void	SetTest::testConstructor() {
	testPerTypeConstructor(Source<t_int>(200));
	testPerTypeConstructor(Source<t_str>(30));
	testPerTypeConstructor(Source<t_dummy>(100));
	testPerTypeConstructor(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/

template<class T>
void	SetTest::testPerTypeIterator(const Source< ft::set<T> >& src) {
	typedef	ft::set<T>	t_set;
	logTitleSection(src.type);

	t_set	set(src.data);
	logTitleSubSection("Iterator - from begin ++ to end");
	for (typename t_set::iterator it = set.begin(); it != set.end(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';

	logTitleSubSection("Iterator - from end --");
	typename t_set::iterator ite = set.end();
	for (size_t i = 0; i < set.size(); ++i) {
		--ite;
		PRINT << *ite << ' ';
	}
	PRINT << '\n';

	logTitleSubSection("Const Iterator - from begin ++ to end");
	for (typename t_set::const_iterator it = set.begin(); it != set.end(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';


	logTitleSubSection("Reverse Iterator - from rbegin ++ to rend");
	for (typename t_set::reverse_iterator it = set.rbegin(); it != set.rend(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';

	logTitleSubSection("Reverse Iterator - from rend --");
	typename t_set::reverse_iterator reit = set.rend();
	for (size_t i = 0; i < set.size(); ++i) {
		--reit;
		PRINT << *reit << ' ';
	}
	PRINT << '\n';

	logTitleSubSection("Const Reverse Iterator - from rbegin ++ to rend");
	for (typename t_set::const_reverse_iterator it = set.rbegin(); it != set.rend(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';
}

void	SetTest::testIterator() {
	testPerTypeIterator(Source<t_int>(200));
	testPerTypeIterator(Source<t_str>(30));
	testPerTypeIterator(Source<t_dummy>(100));
	testPerTypeIterator(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/

template<class T>
void	SetTest::testPerTypeCapacity(const Source< ft::set<T> >& src) {
	typedef	ft::set<T>	t_set;
	logTitleSection(src.type);

	logTitleSubSection("empty - size");
	t_set	empty_set;
	PRINT << src.data.empty() << ' ' << src.data.size() << '\n';
	PRINT << empty_set.empty() << ' ' << empty_set.size() << '\n';
	//Note: skip max_size() because allocator is based on node type.	
}


void	SetTest::testCapacity() {
	testPerTypeCapacity(Source<t_int>(200));
	testPerTypeCapacity(Source<t_str>(30));
	testPerTypeCapacity(Source<t_dummy>(100));
	testPerTypeCapacity(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
template<class T>
void	SetTest::testPerTypeElementAccess(const Source< ft::set<T> >& src) {
}

void	SetTest::testElementAccess() {
	testPerTypeElementAccess(Source<t_int>(200));
	testPerTypeElementAccess(Source<t_str>(30));
	testPerTypeElementAccess(Source<t_dummy>(100));
	testPerTypeElementAccess(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/

template<class T>
void	SetTest::testPerTypeModifiers(const Source< ft::set<T> >& src) {
	typedef	ft::set<T>	t_set;
	typedef	typename t_set::iterator iterator;
	typedef	typename t_set::const_iterator const_iterator;
	logTitleSection(src.type);

	logTitleSubSection("insert - single value");
	t_set	set;
	const_iterator	it = src.data.begin();
	ft::pair<iterator, bool> pair;
	for (int i = 0; i < 5; ++i) {
		const_iterator temp = it;
		pair = set.insert(*it); // inserting new value
		PRINT << *pair.first << ' ';
		PRINT << pair.second << ' ';
		pair = set.insert(*temp); // inserting existing value
		PRINT << *pair.first << ' ';
		PRINT << pair.second << ' ';
		++it;
	}
	PRINT << '\n';
	printSet(set);

	logTitleSubSection("insert - hint");
	iterator	hint = set.insert(pair.first, *it);
	PRINT << *hint << ' ';
	++it;
	hint = set.insert(set.begin(), *it);
	PRINT << *hint << ' ';
	printSet(set);

	logTitleSubSection("insert - range");
	set.insert(src.data.begin(), src.data.end());
	printSet(set);

	logTitleSubSection("erase - iterator");
	iterator it_valid = set.end(); // for iterator validity check
	--it_valid;
	PRINT << *it_valid << ' ';
	set.erase(set.begin());
	printSet(set);
	PRINT << *it_valid << ' '; // check iterator validity after erase

	logTitleSubSection("erase - key");
	T k = *set.begin();
	PRINT << set.erase(k) << '\n';
	PRINT << set.erase(k) << '\n';
	printSet(set);
	PRINT << *it_valid << ' '; // check iterator validity after erase

	logTitleSubSection("erase - range");
	iterator begin = set.begin();
	iterator end = it_valid;
	set.erase(++begin, --end);
	printSet(set);
	PRINT << *it_valid << ' '; // check iterator validity after erase

	logTitleSubSection("swap - 2 empty");
	t_set set1;
	t_set set2;
	set1.swap(set2);
	printSet(set1);
	printSet(set2);

	logTitleSubSection("swap - 1 empty");
	set1 = src.data;
	set1.swap(set2);
	printSet(set1);
	printSet(set2);
	set1.swap(set2);
	printSet(set1);
	printSet(set2);

	logTitleSubSection("swap - no empty");
	set2 = src.data;
	for (int i = 0; i < 5; ++ i) {
		set2.erase(set2.begin());
	}
	iterator it_valid_1 = set1.begin(); // for iterator validity check
	iterator it_valid_2 = set2.begin(); // for iterator validity check
	set1.swap(set2);
	printSet(set1);
	printSet(set2);
	set1.swap(set2);
	printSet(set1);
	printSet(set2);
	PRINT << *it_valid_1 << ' ';
	PRINT << *it_valid_2 << ' ';

	logTitleSubSection("clear - non-empty");
	set1.clear();
	printSet(set1);
	logTitleSubSection("clear - empty");
	set1.clear();
	printSet(set1);	
}

void	SetTest::testModifiers() {
	testPerTypeModifiers(Source<t_int>(200));
	testPerTypeModifiers(Source<t_str>(30));
	testPerTypeModifiers(Source<t_dummy>(100));
	testPerTypeModifiers(Source<t_dummy_2D>(42));
	#ifdef EXTREME
		logTitleSubSection("insert/erase - large amount");
		t_int	set;
		std::size_t max_size = EXTREME_SET;
		for (std::size_t i = 0; i < max_size; ++i) {
			set.insert(i);
		}
		for (std::size_t i = 0; i < max_size + 10; ++i) {
			t_int::iterator it = set.find(i);
			if (it != set.end()) {
				PRINT << 'Y';
			}
			else {
				PRINT << 'N';
			}
		}
		PRINT << '\n';
		printContainerSize(set);
		for (std::size_t i = 0; i < max_size; ++i) {
			set.erase(i);
		}
		printContainerSize(set);
	#endif
}

/*********************************************/ 
/**				operator					**/ 
/*********************************************/

template<class T>
void	SetTest::testPerTypeOperator(const Source< ft::set<T> >& src) {
	typedef	ft::set<T>	t_set;
	typedef	typename t_set::iterator iterator;
	typedef	typename t_set::const_iterator const_iterator;
	logTitleSection(src.type);

	logTitleSubSection("find & count");
	t_set	set(src.data);
	for (const_iterator it_src = src.data.begin(); it_src != src.data.end(); ++it_src) {
		T	k = *it_src;
		iterator it = set.find(k);
		if (it != set.end()) {
			PRINT << *it << ' ';
		}
		else {
			PRINT << "[NotFound] ";
		}
		PRINT << set.count(k) << ' ';
		set.erase(it);
		it = set.find(k);
		if (it != set.end()) {
			PRINT << *it << ' ';
		}
		else {
			PRINT << "[NotFound] ";
		}
		PRINT << set.count(k) << ' ';
	}

	logTitleSubSection("lower/upper bound");
	set = src.data;
	iterator	it_first = set.begin();
	iterator	it_last = set.end();
	--it_last;
	iterator	it_begin = set.lower_bound(*it_first);
	iterator	it_end = set.upper_bound(*it_last);
	set.erase(it_begin, it_end);
	printSet(set);

	logTitleSubSection("equal range");
	set = src.data;
	it_first = set.begin();
	it_last = set.end();
	--it_last;
	ft::pair<iterator, iterator>	pair1 = set.equal_range(*it_first);
	ft::pair<iterator, iterator>	pair2 = set.equal_range(*it_last);
	set.erase(pair1.first, pair1.second);
	set.erase(pair2.first, pair2.second);
	printSet(set);
}

void	SetTest::testBound() {
	logTitleSubSection("lower/upper bound - specialt");
	t_int	set;
	for (int i = 0; i < 100; ++i) {
		set.insert(i * 2 - 1);
	}
	printSet(set);
	for (int i = 0; i < 98; ++i) {
		PRINT << *set.lower_bound(i * 2) << ' ';
		PRINT << *set.lower_bound(i * 2 - 1) << ' ';
		PRINT << *set.upper_bound(i * 2) << ' ';
		PRINT << *set.upper_bound(i * 2 - 1) << ' ';
		ft::pair<t_int::iterator, t_int::iterator>	pair = set.equal_range(i * 2 - 1);
		PRINT << *pair.first << ' ';
		PRINT << *pair.second << ' ';
	}
	t_int::iterator it = set.lower_bound(100 * 2);
	if (it == set.end()) {
		PRINT << "end!\n";
	}
	it = set.upper_bound(100 * 2 - 1);
	if (it == set.end()) {
		PRINT << "end!\n";
	}
}

void	SetTest::testOperator() {
	testPerTypeOperator(Source<t_int>(200));
	testPerTypeOperator(Source<t_str>(30));
	testPerTypeOperator(Source<t_dummy>(100));
	testPerTypeOperator(Source<t_dummy_2D>(42));
	testBound();
}

/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	SetTest::testAllocator() {
	int psize;
	t_int		set;
	t_value_int* p;

	p = set.get_allocator().allocate(5);
	psize = sizeof(t_int::value_type) * 5;
	PRINT << "The allocated array has a size of " << psize << " bytes.\n";
	set.get_allocator().deallocate(p, 5);
}

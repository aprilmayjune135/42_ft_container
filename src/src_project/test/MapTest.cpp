#include "MapTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				Source Constructor			**/ 
/*********************************************/

template<>
Source<MapTest::t_int>::Source(std::size_t n): type("int") {
	for (std::size_t i = 0; i < n; ++i) {
		MapTest::t_pair_int	pair(i, 'a' + i % 26);
		data.insert(pair);
	}
}

template<>
Source<MapTest::t_str>::Source(std::size_t n): type("string") {
	static std::string	strings[10] = { "hello", "how", "are", "you", "doing", "today", "?", "I", "feel", "great!" };
	srand(time(NULL));
	for (std::size_t i = 0; i < n; ++i) {
		MapTest::t_pair_str	pair(strings[i % 10], 'a' + i % 26);
		data.insert(pair);
	}
}

template<>
Source<MapTest::t_dummy>::Source(std::size_t n): type("dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i);
		MapTest::t_pair_dummy	pair(d, 'a' + i % 26);
		data.insert(pair);
	}
}

template<>
Source<MapTest::t_dummy_2D>::Source(std::size_t n): type("2D dummy class") {
	for (std::size_t i = 0; i < n; ++i) {
		dummy_type	d(i);
		dummy_type_2D d_2D(d);
		MapTest::t_pair_dummy_2D	pair(d_2D, 'a' + i % 26);
		data.insert(pair);
	}
}

MapTest::MapTest(): ContainerTest("map") {}

/*********************************************/ 
/**				constructor					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeConstructor(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);

	logTitleSubSection("Constructor - default");
	t_map	map_default;
	printMap(map_default);

	logTitleSubSection("Constructor - range");
	t_map	map_range(src.data.begin(), src.data.end());
	printMap(map_range);
	map_range = map_default;
	printMap(map_range);

	logTitleSubSection("Constructor - copy");
	t_map	map_copy(src.data);
	printMap(map_copy);
	map_copy = map_default;
	printMap(map_copy);

	logTitleSubSection("Constructor - operator=");
	t_map	map_assign = src.data;
	printMap(map_assign);
}

void	MapTest::testConstructor() {
	testPerTypeConstructor(Source<t_int>(200));
	testPerTypeConstructor(Source<t_str>(30));
	testPerTypeConstructor(Source<t_dummy>(100));
	testPerTypeConstructor(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeIterator(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);

	t_map	map(src.data);
	logTitleSubSection("Iterator - from begin ++ to end");
	for (typename t_map::iterator it = map.begin(); it != map.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	logTitleSubSection("Iterator - from end --");
	typename t_map::iterator ite = map.end();
	for (size_t i = 0; i < map.size(); ++i) {
		--ite;
		printPair(*ite);
	}
	PRINT << '\n';

	logTitleSubSection("Const Iterator - from begin ++ to end");
	for (typename t_map::const_iterator it = map.begin(); it != map.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';


	logTitleSubSection("Reverse Iterator - from rbegin ++ to rend");
	for (typename t_map::reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	logTitleSubSection("Reverse Iterator - from rend --");
	typename t_map::reverse_iterator reit = map.rend();
	for (size_t i = 0; i < map.size(); ++i) {
		--reit;
		printPair(*reit);
	}
	PRINT << '\n';

	logTitleSubSection("Const Reverse Iterator - from rbegin ++ to rend");
	for (typename t_map::const_reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';
}

void	MapTest::testIterator() {
	testPerTypeIterator(Source<t_int>(200));
	testPerTypeIterator(Source<t_str>(30));
	testPerTypeIterator(Source<t_dummy>(100));
	testPerTypeIterator(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeCapacity(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);

	logTitleSubSection("empty - size");
	t_map	empty_map;
	PRINT << src.data.empty() << ' ' << src.data.size() << '\n';
	PRINT << empty_map.empty() << ' ' << empty_map.size() << '\n';
	//Note: skip max_size() because allocator is based on node type.	
}


void	MapTest::testCapacity() {
	testPerTypeCapacity(Source<t_int>(200));
	testPerTypeCapacity(Source<t_str>(30));
	testPerTypeCapacity(Source<t_dummy>(100));
	testPerTypeCapacity(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/
template<class Key, class T>
void	MapTest::testPerTypeElementAccess(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	typedef	typename ft::map<Key, T>::const_iterator	const_iterator;
	logTitleSection(src.type);

	logTitleSubSection("operator[] insert new pair");
	t_map	map;
	const_iterator it = src.data.begin();
	for (std::size_t i = 0; i < src.data.size() / 2; ++i) {
		map[it->first] = it->second;
		++it;
	}
	printMap(map);
	logTitleSubSection("operator[] change existing pair");
	for (std::size_t i = 0; i < src.data.size() / 2; ++i) {
		const_iterator it_next = it;
		--it;
		map[it->first] = it_next->second;
	}
	printMap(map);
	logTitleSubSection("operator[] access exisiting pair");
	for (const_iterator it_map = map.begin(); it_map != map.end(); ++it_map) {
		PRINT << map[it_map->first] << ' ';
	}
	PRINT << '\n';
}

void	MapTest::testElementAccess() {
	testPerTypeElementAccess(Source<t_int>(200));
	testPerTypeElementAccess(Source<t_str>(30));
	testPerTypeElementAccess(Source<t_dummy>(100));
	testPerTypeElementAccess(Source<t_dummy_2D>(42));
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeModifiers(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	typedef	typename t_map::iterator iterator;
	typedef	typename t_map::const_iterator const_iterator;
	logTitleSection(src.type);

	logTitleSubSection("insert - single value");
	t_map	map;
	const_iterator	it = src.data.begin();
	for (int i = 0; i < 5; ++i) {
		const_iterator temp = it;
		ft::pair<iterator, bool> pair = map.insert(*it); // inserting new value
		printPair(*pair.first);
		PRINT << pair.second << ' ';
		pair = map.insert(*temp); // inserting existing value
		printPair(*pair.first);
		PRINT << pair.second << ' ';
		++it;
	}
	PRINT << '\n';
	printMap(map);

	logTitleSubSection("insert - range");
	map.insert(src.data.begin(), src.data.end());
	printMap(map);

	logTitleSubSection("insert - hint");
	map.insert(src.data.begin(), src.data.end());
	printMap(map);

	logTitleSubSection("erase - iterator");
	iterator it_valid = map.end(); // for iterator validity check
	--it_valid;
	printPair(*it_valid);
	map.erase(map.begin());
	printMap(map);
	printPair(*it_valid); // check iterator validity after erase

	logTitleSubSection("erase - key");
	Key k = map.begin()->first;
	PRINT << map.erase(k) << '\n';
	PRINT << map.erase(k) << '\n';
	printMap(map);
	printPair(*it_valid); // check iterator validity after erase

	logTitleSubSection("erase - range");
	iterator begin = map.begin();
	iterator end = it_valid;
	map.erase(++begin, --end);
	printMap(map);
	printPair(*it_valid); // check iterator validity after erase

	logTitleSubSection("swap - 2 empty");
	t_map map1;
	t_map map2;
	map1.swap(map2);
	printMap(map1);
	printMap(map2);

	logTitleSubSection("swap - 1 empty");
	map1 = src.data;
	map1.swap(map2);
	printMap(map1);
	printMap(map2);
	map1.swap(map2);
	printMap(map1);
	printMap(map2);

	logTitleSubSection("swap - no empty");
	map2 = src.data;
	for (int i = 0; i < 5; ++ i) {
		map2.erase(map2.begin());
	}
	iterator it_valid_1 = map1.begin(); // for iterator validity check
	iterator it_valid_2 = map2.begin(); // for iterator validity check
	map1.swap(map2);
	printMap(map1);
	printMap(map2);
	map1.swap(map2);
	printMap(map1);
	printMap(map2);
	printPair(*it_valid_1);
	printPair(*it_valid_2);

	logTitleSubSection("clear - non-empty");
	map1.clear();
	printMap(map1);
	logTitleSubSection("clear - empty");
	map1.clear();
	printMap(map1);	
}

void	MapTest::testModifiers() {
	testPerTypeModifiers(Source<t_int>(200));
	testPerTypeModifiers(Source<t_str>(30));
	testPerTypeModifiers(Source<t_dummy>(100));
	testPerTypeModifiers(Source<t_dummy_2D>(42));
	#ifdef EXTREME
		logTitleSubSection("insert/erase - large amount");
		t_int	map;
		std::size_t max_size = 1000000;
		for (std::size_t i = 0; i < max_size; ++i) {
			MapTest::t_pair_int	pair(i, 'a' + i % 26);
			map.insert(pair);
		}
		printContainerSize(map);
		for (std::size_t i = 0; i < max_size; ++i) {
			map.erase(i);
		}
		printContainerSize(map);
	#endif
}

/*********************************************/ 
/**				operator					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeOperator(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	typedef	typename t_map::iterator iterator;
	typedef	typename t_map::const_iterator const_iterator;
	logTitleSection(src.type);

	logTitleSubSection("find & count");
	t_map	map(src.data);
	const_iterator it_src = src.data.begin();
	for (int i = 0; i < 10; ++i) {
		Key	k = it_src->first;
		iterator it = map.find(k);
		if (it != map.end()) {
			printPair(*it);
		}
		else {
			PRINT << "[NotFound] ";
		}
		PRINT << map.count(k) << ' ';
		map.erase(it);
		it = map.find(k);
		if (it != map.end()) {
			printPair(*it);
		}
		else {
			PRINT << "[NotFound] ";
		}
		PRINT << map.count(k) << ' ';
		++it_src;
	}

	logTitleSubSection("lower/upper bound");
	map = src.data;
	iterator	it_first = map.begin();
	iterator	it_last = map.end();
	--it_last;
	iterator	it_begin = map.lower_bound(it_first->first);
	iterator	it_end = map.upper_bound(it_last->first);
	map.erase(it_begin, it_end);
	printMap(map);

	logTitleSubSection("equal range");
	map = src.data;
	it_first = map.begin();
	it_last = map.end();
	--it_last;
	ft::pair<iterator, iterator>	pair1 = map.equal_range(it_first->first);
	ft::pair<iterator, iterator>	pair2 = map.equal_range(it_last->first);
	map.erase(pair1.first, pair1.second);
	map.erase(pair2.first, pair2.second);
	printMap(map);
}

void	MapTest::testBound() {
	logTitleSubSection("lower/upper bound - specialt");
	t_int	map;
	for (int i = 0; i < 100; ++i) {
		t_pair_int	pair(i * 2 - 1, 'a' + i % 26);
		map.insert(pair);
	}
	printMap(map);
	for (int i = 0; i < 98; ++i) {
		printPair(*map.lower_bound(i * 2));
		printPair(*map.lower_bound(i * 2 - 1));
		printPair(*map.upper_bound(i * 2));
		printPair(*map.upper_bound(i * 2 - 1));
		ft::pair<t_int::iterator, t_int::iterator>	pair = map.equal_range(i * 2 - 1);
		printPair(*pair.first);
		printPair(*pair.second);
	}
	t_int::iterator it = map.lower_bound(100 * 2);
	if (it == map.end()) {
		PRINT << "end!\n";
	}
	it = map.upper_bound(100 * 2 - 1);
	if (it == map.end()) {
		PRINT << "end!\n";
	}
}

void	MapTest::testOperator() {
	testPerTypeOperator(Source<t_int>(200));
	testPerTypeOperator(Source<t_str>(30));
	testPerTypeOperator(Source<t_dummy>(100));
	testPerTypeOperator(Source<t_dummy_2D>(42));
	testBound();
}

/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	MapTest::testAllocator() {
	int psize;
	t_int		map;
	t_pair_int* p;

	p = map.get_allocator().allocate(5);
	psize = sizeof(t_int::value_type) * 5;
	PRINT << "The allocated array has a size of " << psize << " bytes.\n";
	map.get_allocator().deallocate(p, 5);
}

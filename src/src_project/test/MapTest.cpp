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

void	MapTest::testConstructor() {
	t_int	map;
	for (int i = 100; i > 0; --i) {
		t_pair_int	pair(i, 'a' + i % 26);
		map.insert(pair);
	}
	// #ifndef STANDARD
	// map.print();
	// #endif
	// t_int	map2(map);
	// printMap(map2);
	// t_int	map3;
	// map2 = map3;
	// printMap(map2);
	// t_int	map4(map);
	// map2 = map4;
	// printMap(map2);

	// t_pair_int	pair1(11, 'a');
	// t_pair_int	pair2(0, 'a');
	// t_pair_int	pair3(10, 'a');
	// t_pair_int	pair4(1, 'a');
	// t_pair_int	pair5(30, 'a');
	// t_pair_int	pair6(2, 'a');
	// t_pair_int	pair7(4, 'a');
	// t_pair_int	pair8(3, 'a');

	// map.insert(pair1);
	// map.insert(pair2);
	// map.insert(pair3);
	// map.insert(pair4);
	// map.insert(pair5);
	// map.insert(pair6);
	// map.insert(pair7);
	// map.insert(pair8);


	// PRINT << "size: " << map.size() << '\n';

}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeIterator(Source< ft::map<Key, T> > src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);


	logTitleSubSection("Iterator - from begin ++ to end");
	for (typename t_map::iterator it = src.data.begin(); it != src.data.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	logTitleSubSection("Iterator - from end --");
	typename t_map::iterator ite = src.data.end();
	for (size_t i = 0; i < src.data.size(); ++i) {
		--ite;
		printPair(*ite);
	}
	PRINT << '\n';

	logTitleSubSection("Const Iterator - from begin ++ to end");
	for (typename t_map::const_iterator it = src.data.begin(); it != src.data.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';


	logTitleSubSection("Reverse Iterator - from rbegin ++ to rend");
	for (typename t_map::reverse_iterator it = src.data.rbegin(); it != src.data.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	logTitleSubSection("Reverse Iterator - from rend --");
	typename t_map::reverse_iterator reit = src.data.rend();
	for (size_t i = 0; i < src.data.size(); ++i) {
		--reit;
		printPair(*reit);
	}
	PRINT << '\n';

	logTitleSubSection("Const Reverse Iterator - from rbegin ++ to rend");
	for (typename t_map::const_reverse_iterator it = src.data.rbegin(); it != src.data.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

}

void	MapTest::testIterator() {
	testPerTypeIterator(Source<t_int>(42));
	testPerTypeIterator(Source<t_str>(30));
	testPerTypeIterator(Source<t_dummy>(100));
	testPerTypeIterator(Source<t_dummy_2D>(200));
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/

template<class Key, class T>
void	MapTest::testPerTypeCapacity(const Source< ft::map<Key, T> >& src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);

	t_map	empty_map;

	logTitleSubSection("empty - size");
	PRINT << src.data.empty() << ' ' << src.data.size() << '\n';
	PRINT << empty_map.empty() << ' ' << empty_map.size() << '\n';
	//TODO: to final check:
	//Note: skip max_size() because allocator is based on node type.
	
}


void	MapTest::testCapacity() {
	testPerTypeCapacity(Source<t_int>(42));
	testPerTypeCapacity(Source<t_str>(30));
	testPerTypeCapacity(Source<t_dummy>(100));
	testPerTypeCapacity(Source<t_dummy_2D>(200));
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
	testPerTypeElementAccess(Source<t_int>(42));
	testPerTypeElementAccess(Source<t_str>(30));
	testPerTypeElementAccess(Source<t_dummy>(100));
	testPerTypeElementAccess(Source<t_dummy_2D>(200));
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

	logTitleSubSection("insert - value");
	t_map	map;
	const_iterator	it = src.data.begin();
	for (int i = 0; i < 5; ++i) {
		const_iterator temp = it;
		ft::pair<iterator, bool> pair = map.insert(*it);
		printPair(*pair.first);
		PRINT << pair.second << ' ';
		pair = map.insert(*temp);
		printPair(*pair.first);
		PRINT << pair.second << ' ';
		++it;
	}
	PRINT << '\n';
	printMap(map);

	logTitleSubSection("insert - range");
	map.insert(src.data.begin(), src.data.end());
	printMap(map);

	logTitleSubSection("erase - iterator");
	map.erase(map.begin());
	printMap(map);

	logTitleSubSection("erase - key");
	Key k = map.begin()->first;
	PRINT << map.erase(k) << '\n';
	PRINT << map.erase(k) << '\n';
	printMap(map);

	logTitleSubSection("erase - range");
	iterator begin = map.begin();
	iterator end = map.end();
	map.erase(++begin, --end);
	printMap(map);

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
	map1.swap(map2);
	printMap(map1);
	printMap(map2);
	map1.swap(map2);
	printMap(map1);
	printMap(map2);

	logTitleSubSection("clear - non-empty");
	map1.clear();
	printMap(map1);
	logTitleSubSection("clear - empty");
	map1.clear();
	printMap(map1);	

}

void	MapTest::testModifiers() {
	testPerTypeModifiers(Source<t_int>(42));
	testPerTypeModifiers(Source<t_str>(30));
	testPerTypeModifiers(Source<t_dummy>(100));
	testPerTypeModifiers(Source<t_dummy_2D>(200));
}


/*********************************************/ 
/**				allocator					**/ 
/*********************************************/

void	MapTest::testAllocator() {
	// TODO
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
}

void	MapTest::testBound() {
	logTitleSubSection("lower/upper bound");
	t_int	map;
	for (int i = 0; i < 100; ++i) {
		t_pair_int	pair(i * 2 - 1, 'a' + i % 26);
		map.insert(pair);
	}
	printMap(map);
	for (int i = 0; i < 99; ++i) {
		printPair(*map.lower_bound(i * 2));
		printPair(*map.lower_bound(i * 2 - 1));
		printPair(*map.upper_bound(i * 2));
		printPair(*map.upper_bound(i * 2 - 1));
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
	testPerTypeOperator(Source<t_int>(42));
	testPerTypeOperator(Source<t_str>(30));
	testPerTypeOperator(Source<t_dummy>(100));
	testPerTypeOperator(Source<t_dummy_2D>(200));
	testBound();
}


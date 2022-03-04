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
	printMap(map);

	t_int	map2(map);
	printMap(map2);
	t_int	map3;
	map2 = map3;
	printMap(map2);
	t_int	map4(map);
	map2 = map4;
	printMap(map2);

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
	
	logTitleSubSection("find");
	Key	k = src.data.begin()->first;
	typename t_map::const_iterator it = src.data.find(k);
	printPair(*it);
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
void	MapTest::testPerTypeElementAccess(Source< ft::map<Key, T> > src) {
	typedef	ft::map<Key, T>	t_map;
	logTitleSection(src.type);

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
void	MapTest::testPerTypeModifiers(Source< ft::map<Key, T> > src) {
	typedef	ft::map<Key, T>	t_map;
	typedef	typename t_map::iterator iterator;
	logTitleSection(src.type);

	logTitleSubSection("erase - iterator");
	src.data.erase(src.data.begin());
	printMap(src.data);

	logTitleSubSection("erase - key");
	PRINT << src.data.erase(src.data.begin()->first) << '\n';
	printMap(src.data);

	logTitleSubSection("erase - range");
	iterator begin = src.data.begin();
	iterator end = src.data.end();
	src.data.erase(++begin, --end);
	printMap(src.data);

}

void	MapTest::testModifiers() {
	testPerTypeModifiers(Source<t_int>(42));
	testPerTypeModifiers(Source<t_str>(30));
	testPerTypeModifiers(Source<t_dummy>(100));
	testPerTypeModifiers(Source<t_dummy_2D>(200));
	// typedef ft::map<int, char, std::greater<int> > map_type;
	// typedef ft::pair<const int, char>		pair_type;
	// map_type	map;
	// for (std::size_t i = 0; i < 10; ++i) {
	// 	pair_type	pair(i, 'a' + i % 26);
	// 	map.insert(pair);
	// }
	// for (map_type::iterator it = map.begin(); it != map.end(); ++it) {
	// 	printPair(*it);
	// }
	// PRINT << '\n';
	// for (map_type::reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
	// 	printPair(*it);
	// }
	// PRINT << '\n';

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

void	MapTest::testOperator() {
}


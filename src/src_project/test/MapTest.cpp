#include "MapTest.hpp"
#include "../utility/Print.hpp"
#include "../utility/print_container.hpp"
#include "../utility/log_formatting.hpp"

/*********************************************/ 
/**				Source Constructor			**/ 
/*********************************************/

MapTest::MapTest(): ContainerTest("map") {}

/*********************************************/ 
/**				constructor					**/ 
/*********************************************/

void	MapTest::testConstructor() {
	t_int	map;
	// for (int i = 100; i > 0; --i) {
	// 	t_pair	pair(i, 'a' + i % 26);
	// 	map.insert(pair);
	// }

	t_pair	pair1(5, 'a');
	t_pair	pair2(0, 'b');
	t_pair	pair3(10, 'c');
	t_pair	pair4(1, 'd');

	map.insert(pair1);
	map.insert(pair2);
	map.insert(pair3);
	map.insert(pair4);

	#ifndef STANDARD
	map.print();
	#endif

	PRINT << "size: " << map.size() << '\n';

	PRINT << "From begin ++\n";
	t_int::iterator itb = map.begin();
	for (size_t i = 0; i < map.size(); ++i) {
		printPair(*itb);
		++itb;
	}
	PRINT << '\n';

	PRINT << "From end --\n";
	t_int::iterator ite = map.end();
	for (size_t i = 0; i < map.size(); ++i) {
		--ite;
		printPair(*ite);
	}
	PRINT << '\n';

	PRINT << "From begin ++ to end\n";
	for (t_int::iterator it = map.begin(); it != map.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	PRINT << "From rbegin ++ to rend\n";
	for (t_int::reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';

	PRINT << "From rbegin ++\n";
	t_int::reverse_iterator rbit = map.rbegin();
	for (size_t i = 0; i < map.size(); ++i) {
		printPair(*rbit);
		++rbit;
	}
	PRINT << '\n';

	PRINT << "From rend --\n";
	t_int::reverse_iterator reit = map.rend();
	for (size_t i = 0; i < map.size(); ++i) {
		--reit;
		printPair(*reit);
	}
	PRINT << '\n';



}

/*********************************************/ 
/**				iterator					**/ 
/*********************************************/

void	MapTest::testIterator() {
}

/*********************************************/ 
/**				capacity					**/ 
/*********************************************/

void	MapTest::testCapacity() {
}

/*********************************************/ 
/**				element access				**/ 
/*********************************************/

void	MapTest::testElementAccess() {
}

/*********************************************/ 
/**				modifier					**/ 
/*********************************************/

void	MapTest::testModifiers() {
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


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
	for (int i = 20; i > 0; --i) {
		t_pair	pair(i, 'a' + i);
		map.insert(pair);
	}	
	#ifndef STANDARD
	map.print();
	PRINT << "size: " << map.size() << '\n';
	PRINT << "From begin ++\n";
	t_int::iterator itb = map.begin();
	for (int i = 0; i < 10; ++i) {
		++itb;
		PRINT << *itb << ' ';
	}
	PRINT << '\n';

	PRINT << "From end --\n";
	t_int::iterator ite = map.end();
	for (int i = 0; i < 10; ++i) {
		--ite;
		PRINT << *ite << ' ';
	}
	PRINT << '\n';

	PRINT << "From begin ++ to end\n";
	for (t_int::iterator it = map.begin(); it != map.end(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';

	PRINT << "From rbegin ++ to rend\n";
	for (t_int::reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
		PRINT << *it << ' ';
	}
	PRINT << '\n';

	PRINT << "From rbegin ++\n";
	t_int::reverse_iterator rbit = map.rbegin();
	for (int i = 0; i < 10; ++i) {
		++rbit;
		PRINT << *rbit << ' ';
	}
	PRINT << '\n';

	PRINT << "From rend --\n";
	t_int::reverse_iterator reit = map.rend();
	for (int i = 0; i < 10; ++i) {
		--reit;
		PRINT << *reit << ' ';
	}
	PRINT << '\n';

	#endif

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


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
	for (t_int::iterator it = map.begin(); it != map.end(); ++it) {
		PRINT << *it << ' ';
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


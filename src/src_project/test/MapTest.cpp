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
	#endif
	t_pair	pair1(3, 'a');
	t_pair	pair2(2, 'a');
	PRINT << map.value_comp()(pair1, pair2) << '\n';
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


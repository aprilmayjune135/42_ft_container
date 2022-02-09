#include "test.hpp"
#include "../container/vector.hpp"
#include <vector>

namespace vector {
void	testConstructor() {
	version::vector<int> vec(10, 999);
	PRINT << "This is vector constructor!\n";
	PRINT << *(vec.begin()) << '\n';
}

void	testIterator() {
	PRINT << "This is vector iterator!\n";
}

void	testCapacity() {
	PRINT << "This is vector capacity!\n";
}

void	testElementAccess() {
	PRINT << "This is vector element access!\n";
}

void	testModifiers() {
	PRINT << "This is vector modifiers!\n";
}

void	testAllocator() {
	PRINT << "This is vector allocator!\n";
}

void	testOperator() {
	PRINT << "This is vector operator!\n";
}

} /* end of namespace vector */

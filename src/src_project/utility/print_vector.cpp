#include "print_vector.hpp"
#include <iostream>

namespace utility {

template<class Iterator>
void	printVector(Iterator begin, Iterator end) {
	for (Iterator it = begin; it != end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
}

} /* end of namespace utility */

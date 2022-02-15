#pragma once
#include <string>
#include "Print.hpp"

template <class C>
void	printVector(const C& vector) {
	if (vector.empty()) {
		PRINT << "Empty container!";
	}
	else {
		for (typename C::const_iterator it = vector.begin(); it != vector.end(); ++it) {
			PRINT << *it << " ";
		}
	}
	PRINT << '\n';
}

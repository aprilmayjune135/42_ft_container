#pragma once
#include <string>
#include "Print.hpp"

template <class C>
void	printVectorCapacity(const C& vector) {
	PRINT << "size " << vector.size() << " | capacity " << vector.capacity() << " | max_size " << vector.max_size()<< '\n';
}

template <class C>
void	printVectorData(const C& vector) {
	for (typename C::const_iterator it = vector.begin(); it != vector.end(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
}

template <class C>
void	printVectorDataReverse(const C& vector) {
	for (typename C::const_reverse_iterator it = vector.rbegin(); it != vector.rend(); ++it) {
		PRINT << *it << " ";
	}
	PRINT << '\n';
}

template <class C>
void	printVector(const C& vector) {
	printVectorCapacity(vector);
	printVectorData(vector);
}

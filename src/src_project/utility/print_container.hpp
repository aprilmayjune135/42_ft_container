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

template <class T>
void	printPair(const T& pair) {
	PRINT << pair.first << "(" << pair.second << ") ";
}

template <class C>
void	printMapSize(const C& map) {
	PRINT << "size " << map.size() << '\n';
}

template <class C>
void	printMapData(const C& map) {
	for (typename C::const_iterator it = map.begin(); it != map.end(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';
}

template <class C>
void	printMapDataReverse(const C& map) {
	for (typename C::const_reverse_iterator it = map.rbegin(); it != map.rend(); ++it) {
		printPair(*it);
	}
	PRINT << '\n';
}

template <class C>
void	printMap(const C& map) {
	printMapSize(map);
	printMapData(map);
	printMapDataReverse(map);
}

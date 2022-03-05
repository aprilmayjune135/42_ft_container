#pragma once
#include <cstddef>

/* return only unsigned int, assume last is always bigger than first */
template <class InputIterator>
std::size_t	iteratorDistance(InputIterator first, InputIterator last) {
	std::size_t	ret = 0;
	while (first != last) {
		++first;
		++ret;
	}
	return ret;
}

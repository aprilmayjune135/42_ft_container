#pragma once
#include <cstddef>
#include "../iterator/iterator_traits.hpp"

/* return only unsigned int, assume last is always bigger than first */
template <class InputIterator>
std::size_t	iteratorDistance(InputIterator first, InputIterator last, typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0) {
	std::size_t	ret = 0;
	while (first != last) {
		++first;
		++ret;
	}
	return ret;
}

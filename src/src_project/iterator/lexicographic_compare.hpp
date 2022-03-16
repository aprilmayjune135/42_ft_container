#pragma once
#include "iterator_traits.hpp"

namespace ft {

template <class InputIterator1, class InputIterator2>
bool	lexicographic_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, typename iterator_traits<InputIterator1>::iterator_category* dummy1 = 0, typename iterator_traits<InputIterator2>::iterator_category* dummy2 = 0) {
	(void)dummy1;
	(void)dummy2;
	while (first1 != last1) {
		if (first2 == last2 || *first2 < *first1) {
			return false;
		}
		else if (*first1 < *first2) {
			return true;
		}
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool	lexicographic_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp, typename iterator_traits<InputIterator1>::iterator_category* dummy1 = 0, typename iterator_traits<InputIterator2>::iterator_category* dummy2 = 0) {
	(void)dummy1;
	(void)dummy2;
	while (first1 != last1) {
		if (first2 == last2 || comp(*first2, *first1)) {
			return false;
		}
		else if (comp(*first1, *first2)) {
			return true;
		}
		++first1;
		++first2;
	}
	return (first2 != last2);
}


} /* end of namespace ft */

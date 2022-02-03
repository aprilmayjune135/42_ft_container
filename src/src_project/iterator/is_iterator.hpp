#pragma once
#include "void_t.hpp"

namespace ft {

template <typename T, typename = void>
struct is_iterator {
	const static bool	value = false;
};

template <typename T>
struct is_iterator<T, typename void_t<typename T::iterator_category>::type > {
	const static bool	value = true;
};

template <typename T>
struct is_iterator<T*> {
	const static bool	value = true;
};

} /* end of namespace ft */

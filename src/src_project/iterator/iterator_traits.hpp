#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include <cstddef>

namespace ft {

/*
**	Iterator tages.
**	These are empty types, used to distinguish different iterators.
*/

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag  : public bidirectional_iterator_tag {};

/*
**	Iterator traits.
*/

template<class Iter, typename = typename enable_if<is_iterator<Iter>::value, Iter>::type>
struct iterator_traits {
	typedef typename Iter::difference_type 		difference_type;
	typedef typename Iter::value_type 		  	value_type;
	typedef typename Iter::pointer 			    pointer;
	typedef typename Iter::reference 			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*> {
	typedef std::ptrdiff_t 					difference_type;
	typedef T 								value_type;
	typedef T* 								pointer;
	typedef T& 								reference;
	typedef random_access_iterator_tag		iterator_category;
};

template<class T>
struct iterator_traits<const T*> {
	typedef std::ptrdiff_t 					difference_type;
	typedef T 								value_type;
	typedef const T* 						pointer;
	typedef const T& 						reference;
	typedef random_access_iterator_tag		iterator_category;
};


} /* end of namespace ft */

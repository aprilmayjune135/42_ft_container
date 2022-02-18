#pragma once
#include "../pair/pair.hpp"
#include "../iterator/BidirectionalIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include <memory>
#include <iostream>

namespace ft {

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
class map {
	public:
	/**** member types ****/
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const key_type, mapped_type>		value_type;
		typedef Compare									key_compare;
		// typedef ??? //TODO: to add value_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value&							const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef BidirectionalIterator<value_type>		iterator;
		typedef BidirectionalIterator<const value_type>	const_iterator;
		typedef ReverseIterator<iterator>				reverse_iterator;
		typedef ReverseIterator<const_iterator>			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef std::size_t		size_type;

	/**** key protected member ****/
	private:
		allocator_type	allocator;
		pointer			data;
		size_type		data_size;
		size_type		data_capacity;
	
	public:
	/**** constructor & destructor & operator ****/
		explicit map(const key_compare&comp = key_compare(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map(const map& src);
		~map();
		map&	operator=(const map& rhs);


};

} /* end of namespace ft */

#pragma once
#include "BidirectionalIterator.hpp"

namespace ft{

template <class T, class Category = random_access_iterator_tag>
class RandomAccessIterator : public BidirectionalIterator<Category, T> {
	/**** typedef ****/
	public:
		typedef typename BidirectionalIterator::value_type		value_type;
		typedef typename BidirectionalIterator::difference_type	difference_type;
		typedef typename BidirectionalIterator::pointer			pointer;
		typedef typename BidirectionalIterator::const_pointer		const_pointer;
		typedef typename BidirectionalIterator::reference			reference;
		typedef typename BidirectionalIterator::const_reference	const_reference;
		typedef typename BidirectionalIterator::iterator_category	iterator_category;
	
	public:
	/**** constructor & destructor ****/
		RandomAccessIterator(): BidirectionalIterator() {};
		RandomAccessIterator(const RandomAccessIterator& src): p(src.p) {};
		virtual ~RandomAccessIterator() {};

	/**** operator - equal ****/
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) {
			p = rhs.p;
			return *this;
		};
		bool	operator==(const RandomAccessIterator& rhs) const { return p == rhs.p; };
		bool	operator!=(const RandomAccessIterator& rhs) const { return p != rhs.p; };

	/**** operator - dereference ****/
		reference		operator*() { return *p; };
		const_reference	operator*() const { return *p; };
		reference		operator->() { return *p; };
		const_reference	operator->() const { return *p; };

	/**** operator - prefix/postfix ++/-- ****/
		RandomAccessIterator&			operator++() { 
			++p;
			return *this;
		};
		const RandomAccessIterator	operator++(int) {
			const RandomAccessIterator	old(*this);
			++p;
			return old;
		};
		RandomAccessIterator&			operator--() { 
			--p;
			return *this;
		};
		const RandomAccessIterator	operator--(int) {
			const RandomAccessIterator	old = *this;
			--p;
			return old;
		};

};

} /* end of namespace ft */

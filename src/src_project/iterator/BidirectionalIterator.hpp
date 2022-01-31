#pragma once
#include "iterator_traits.hpp"
#include "Iterator.hpp"

namespace ft{

template <class T, class Category = bidirectional_iterator_tag>
class BidirectionalIterator : public Iterator<Category, T> {
	/**** typedef ****/
	public:
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::const_pointer		const_pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::const_reference		const_reference;
		typedef typename Iterator::iterator_category	iterator_category;
	
	public:
	/**** constructor & destructor ****/
		BidirectionalIterator(): p(NULL) {};
		BidirectionalIterator(const BidirectionalIterator& src): p(src.p) {};
		virtual ~BidirectionalIterator() {};

	/**** operator - equal ****/
		BidirectionalIterator&	operator=(const BidirectionalIterator& rhs) {
			p = rhs.p;
			return *this;
		};
		bool	operator==(const BidirectionalIterator& rhs) const { return p == rhs.p; };
		bool	operator!=(const BidirectionalIterator& rhs) const { return p != rhs.p; };

	/**** operator - dereference ****/
		reference		operator*() { return *p; };
		const_reference	operator*() const { return *p; };
		reference		operator->() { return *p; };
		const_reference	operator->() const { return *p; };

	/**** operator - prefix/postfix ++/-- ****/
		BidirectionalIterator&			operator++() { 
			++p;
			return *this;
		};
		const BidirectionalIterator	operator++(int) {
			const BidirectionalIterator	old(*this);
			++p;
			return old;
		};
		BidirectionalIterator&			operator--() { 
			--p;
			return *this;
		};
		const BidirectionalIterator	operator--(int) {
			const BidirectionalIterator	old = *this;
			--p;
			return old;
		};

};

} /* end of namespace ft */

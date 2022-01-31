#pragma once
#include "iterator_traits.hpp"
#include "Iterator.hpp"

namespace ft{

template <class T, class Category = bidirectional_iterator_tag>
class BidirectionalIterator : public Iterator<Category, T> {
	/**** typedef ****/
	public:
		typedef	Iterator<Category, T>						base_iterator;
		typedef typename base_iterator::value_type			value_type;
		typedef typename base_iterator::difference_type		difference_type;
		typedef typename base_iterator::pointer				pointer;
		typedef typename base_iterator::const_pointer		const_pointer;
		typedef typename base_iterator::reference			reference;
		typedef typename base_iterator::const_reference		const_reference;
		typedef typename base_iterator::iterator_category	iterator_category;
	
	public:
	/**** constructor & destructor ****/
		BidirectionalIterator(): base_iterator() {};
		BidirectionalIterator(const BidirectionalIterator& src) { *this = src; };
		BidirectionalIterator(pointer p_src): base_iterator(p_src) {};
		virtual ~BidirectionalIterator() {};

	/**** operator - equal ****/
		BidirectionalIterator&	operator=(const BidirectionalIterator& rhs) {
			this->p = rhs.p;
			return *this;
		};
		bool	operator==(const BidirectionalIterator& rhs) const { return this->p == rhs.p; };
		bool	operator!=(const BidirectionalIterator& rhs) const { return this->p != rhs.p; };

	/**** operator - dereference ****/
		reference		operator*() { return *this->p; };
		const_reference	operator*() const { return *this->p; };
		reference		operator->() { return *this->p; };
		const_reference	operator->() const { return *this->p; };

	/**** operator - prefix/postfix ++/-- ****/
		BidirectionalIterator&			operator++() { 
			++this->p;
			return *this;
		};
		const BidirectionalIterator	operator++(int) {
			const BidirectionalIterator	old(*this);
			++this->p;
			return old;
		};
		BidirectionalIterator&			operator--() { 
			--this->p;
			return *this;
		};
		const BidirectionalIterator	operator--(int) {
			const BidirectionalIterator	old(*this);
			--this->p;
			return old;
		};

};

} /* end of namespace ft */

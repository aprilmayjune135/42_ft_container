#pragma once
#include "BidirectionalIterator.hpp"

namespace ft{

template <class T, class Category = random_access_iterator_tag>
class RandomAccessIterator : public BidirectionalIterator<Category, T> {
	/**** typedef ****/
	public:
		typedef BidirectionalIterator<Category, T> 				bidirectional_iterator;
		typedef typename bidirectional_iterator::value_type		value_type;
		typedef typename bidirectional_iterator::difference_type	difference_type;
		typedef typename bidirectional_iterator::pointer			pointer;
		typedef typename bidirectional_iterator::const_pointer		const_pointer;
		typedef typename bidirectional_iterator::reference			reference;
		typedef typename bidirectional_iterator::const_reference	const_reference;
		typedef typename bidirectional_iterator::iterator_category	iterator_category;
		typedef	std::size_t	size_type;

	public:
	/**** constructor & destructor ****/
		RandomAccessIterator(): bidirectional_iterator() {};
		RandomAccessIterator(pointer p_src): bidirectional_iterator(p_src) {};
		RandomAccessIterator(const RandomAccessIterator& src) { *this = src; };
		virtual ~RandomAccessIterator() {};

	/**** operator - equal ****/
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) {
			this->p = rhs.p;
			return *this;
		};

	/**** operator - arithmetic ****/
	const RandomAccessIterator	operator+(difference_type n) const {
		const RandomAccessIterator	ret(*this);
		ret.p = this->p + n;
		return ret;
	};
	friend const RandomAccessIterator	operator+(difference_type n, const RandomAccessIterator& a) {
		return a + n;
	};
	const RandomAccessIterator	operator-(difference_type n) const {
		const RandomAccessIterator	ret(*this);
		ret.p = this->p - n;
		return ret;
	};
	friend difference_type	operator-(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
		return lhs.p - rhs.p;
	};

	/**** operator - inequality rational ****/
	friend bool	operator<(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs - rhs) < 0; };
	friend bool	operator<=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs- rhs) <= 0; };
	friend bool	operator>(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs - rhs) > 0; };
	friend bool	operator>=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs- rhs) >= 0; };

	/**** operator - compound assignment ****/
	RandomAccessIterator&	operator+=(difference_type n) {
		this->p += n;
		return *this;
	};
	RandomAccessIterator&	operator-=(difference_type n) {
		this->p -= n;
		return *this;
	};

	/**** operator - offset dereference ****/
	value_type&	operator[](difference_type n) const {
		return *(this->p + n);
	}
};

} /* end of namespace ft */

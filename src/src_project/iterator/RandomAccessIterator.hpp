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
		bool	operator==(const RandomAccessIterator& rhs) const { return this->p == rhs.p; };
		bool	operator!=(const RandomAccessIterator& rhs) const { return this->p != rhs.p; };

	/**** operator - dereference ****/
		reference		operator*() { return *this->p; };
		const_reference	operator*() const { return *this->p; };
		reference		operator->() { return *this->p; };
		const_reference	operator->() const { return *this->p; };

	/**** operator - prefix/postfix ++/-- ****/
		RandomAccessIterator&			operator++() { 
			++this->p;
			return *this;
		};
		const RandomAccessIterator	operator++(int) {
			const RandomAccessIterator	old(*this);
			++this->p;
			return old;
		};
		RandomAccessIterator&			operator--() { 
			--this->p;
			return *this;
		};
		const RandomAccessIterator	operator--(int) {
			const RandomAccessIterator	old(*this);
			--this->p;
			return old;
		};

	/**** operator - arithmetic ****/
	friend const RandomAccessIterator	operator+(const RandomAccessIterator& a, size_type n) {
		const RandomAccessIterator	ret(a);
		ret.p = a.p + n;
		return ret;
	};
	friend const RandomAccessIterator	operator+(size_type n, const RandomAccessIterator& a) {
		return a + n;
	};
	friend const RandomAccessIterator	operator-(const RandomAccessIterator& a, size_type n) {
		const RandomAccessIterator	ret(a);
		ret.p = a.p - n;
		return ret;
	};
	friend difference_type	operator-(const RandomAccessIterator& a, const RandomAccessIterator& b) {
		return a.p - b.p;
	};

	/**** operator - inequality rational ****/
	friend bool	operator<(const RandomAccessIterator& a, const RandomAccessIterator& b) {
		return (a - b) < 0;
	};
	friend bool	operator<=(const RandomAccessIterator& a, const RandomAccessIterator& b) {
		return (a - b) <= 0;
	};
	friend bool	operator>(const RandomAccessIterator& a, const RandomAccessIterator& b) {
		return (a - b) > 0;
	};
	friend bool	operator>=(const RandomAccessIterator& a, const RandomAccessIterator& b) {
		return (a - b) >= 0;
	};

	/**** operator - compound assignment ****/
	RandomAccessIterator&	operator+=(size_type n) {
		this->p += n;
		return *this;
	};
	RandomAccessIterator&	operator-=(size_type n) {
		this->p -= n;
		return *this;
	};

	/**** operator - offset dereference ****/
	value_type&	operator[](size_type n) {
		return *this->p;
	}
};

} /* end of namespace ft */

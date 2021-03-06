#pragma once
#include "BidirectionalIterator.hpp"

namespace ft{

template <class T, class Category = random_access_iterator_tag>
class RandomAccessIterator : public BidirectionalIterator<T, Category> {
	public:
	/**** member types ****/
		typedef BidirectionalIterator<T, Category> 				bidirectional_iterator;
		typedef typename bidirectional_iterator::value_type		value_type;
		typedef typename bidirectional_iterator::difference_type	difference_type;
		typedef typename bidirectional_iterator::pointer			pointer;
		typedef typename bidirectional_iterator::const_pointer		const_pointer;
		typedef typename bidirectional_iterator::reference			reference;
		typedef typename bidirectional_iterator::const_reference	const_reference;
		typedef typename bidirectional_iterator::iterator_category	iterator_category;
		typedef RandomAccessIterator<const T>						const_iterator;
		typedef	std::size_t	size_type;

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

	/**** operator - implicit conversion to const_iterator ****/
		operator const_iterator() const {
			return this->p;
		};

	/**** operator - arithmetic ****/
		const RandomAccessIterator	operator+(difference_type n) const {
			return RandomAccessIterator(this->p + n);
		};
		const RandomAccessIterator	operator-(difference_type n) const {
			return RandomAccessIterator(this->p - n);
		};
		difference_type	operator-(const RandomAccessIterator& rhs) const {
			return this->p - rhs.p;
		};

	/**** operator - inequality rational ****/
		friend bool	operator<(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return lhs.p < rhs.p; };
		friend bool	operator<=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return lhs.p <= rhs.p; };
		friend bool	operator>(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return lhs.p > rhs.p; };
		friend bool	operator>=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return lhs.p >= rhs.p; };

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

/**** non-member operator overload ****/
template <class T, class Category>
const RandomAccessIterator<T, Category>	operator+(typename RandomAccessIterator<T, Category>::difference_type n, const RandomAccessIterator<T, Category>& a) {
	return a + n;
}

} /* end of namespace ft */

#pragma once
#include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class ReverseIterator {
	/**** typedef ****/
	public:
		typedef Iterator	iterator_type;
		typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef	typename iterator_traits<Iterator>::value_type			value_type;
		typedef	typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef	typename iterator_traits<Iterator>::pointer				pointer;
		typedef	typename iterator_traits<Iterator>::reference			reference;

	/**** typedef ****/
	private:
		iterator_type	base_iterator;
	
	public:
	/**** constructor ****/
		ReverseIterator(): base_iterator() {};
		explicit ReverseIterator(iterator_type it): base_iterator(it) {};
		ReverseIterator(const ReverseIterator& rev_it): base_iterator(rev_it.base_iterator) {};
	
	/**** base ****/
		iterator_type	base() const { return base_iterator; };
	
	/**** operator - dereference ****/
		reference	operator*() const { return *(base_iterator - 1); };
		pointer		operator->() const { return &(operator*()); };
		reference	operator[](difference_type n) const { return base_iterator()[-n - 1]; }
	
	/**** operator - prefix/postfix ++/-- ****/
		ReverseIterator&	operator++() {
			--base_iterator;
			return *this;
		};
		const ReverseIterator		operator++(int) {
			const ReverseIterator	old(*this);
			--base_iterator;
			return old;
		};
		ReverseIterator&	operator--() {
			++base_iterator;
			return *this;
		};
		const ReverseIterator		operator--(int) {
			const ReverseIterator	old(*this);
			++base_iterator;
			return old;
		};

	/**** operator - arithmetic ****/
		const ReverseIterator	operator+(difference_type n) const { return ReverseIterator(base_iterator - n); };
		friend const ReverseIterator operator+(difference_type n, const ReverseIterator& a) { return a + n; };
		const ReverseIterator	operator-(difference_type n) const { return ReverseIterator(base_iterator + n); };
		friend const ReverseIterator operator-(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() - rhs.base(); };

	/**** operator - compound assignment ****/
		ReverseIterator&	operator+=(difference_type n) {
			base_iterator -= n;
			return *this;
		};
		ReverseIterator&	operator-=(difference_type n) {
			base_iterator += n;
			return *this;
		};

	/**** operator - relational ****/
		friend bool	operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() == rhs.base(); };
		friend bool	operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() != rhs.base(); };
		friend bool	operator<(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() < rhs.base(); };
		friend bool	operator<=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() <= rhs.base(); };
		friend bool	operator>(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() > rhs.base(); };
		friend bool	operator>=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base() >= rhs.base(); };
};

} /* end of namespace ft */

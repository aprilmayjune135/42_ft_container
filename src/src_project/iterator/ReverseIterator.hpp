#pragma once
#include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class ReverseIterator {
	public:
	/**** member types ****/
		typedef Iterator	iterator_type;
		typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef	typename iterator_traits<Iterator>::value_type			value_type;
		typedef	typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef	typename iterator_traits<Iterator>::pointer				pointer;
		typedef	typename iterator_traits<Iterator>::reference			reference;

	private:
		iterator_type	base_iterator;
	
	public:
	/**** constructor ****/
		ReverseIterator(): base_iterator() {};
		explicit ReverseIterator(iterator_type it): base_iterator(it) {};
		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter>& rev_it): base_iterator(rev_it.base()) {};

	/**** base ****/
		iterator_type	base() const { return base_iterator; };
	
	/**** operator - dereference ****/
		reference	operator*() const { 
			iterator_type	temp = base_iterator - 1;
			return *temp;
		};
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
		const ReverseIterator	operator-(difference_type n) const { return ReverseIterator(base_iterator + n); };
		const ReverseIterator	operator-(const ReverseIterator& rhs) { return ReverseIterator(base_iterator - rhs.base_iterator); };

	/**** operator - compound assignment ****/
		ReverseIterator&	operator+=(difference_type n) {
			base_iterator -= n;
			return *this;
		};
		ReverseIterator&	operator-=(difference_type n) {
			base_iterator += n;
			return *this;
		};

	//TODO: to delete
	// /**** operator - relational ****/
	// 	friend bool	operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator == rhs.base_iterator; };
	// 	friend bool	operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator != rhs.base_iterator; };
	// 	friend bool	operator<(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator < rhs.base_iterator; };
	// 	friend bool	operator<=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator <= rhs.base_iterator; };
	// 	friend bool	operator>(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator > rhs.base_iterator; };
	// 	friend bool	operator>=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return lhs.base_iterator >= rhs.base_iterator; };
};


/**** non-member function overload ****/
template <class Iterator>
const ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator>& a) {
	return a + n;
}
template <class Iterator1, class Iterator2>
bool	operator==(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() == rhs.base(); }

template <class Iterator1, class Iterator2>
bool	operator!=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() != rhs.base(); }

template <class Iterator1, class Iterator2>
bool	operator<(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() < rhs.base(); }

template <class Iterator1, class Iterator2>
bool	operator<=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() <= rhs.base(); }

template <class Iterator1, class Iterator2>
bool	operator>(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() > rhs.base(); }

template <class Iterator1, class Iterator2>
bool	operator>=(const ReverseIterator<Iterator1>& lhs, const ReverseIterator<Iterator2>& rhs) { return lhs.base() >= rhs.base(); }

} /* end of namespace ft */

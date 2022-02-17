#pragma once
#include <cstddef>

namespace ft {

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
class Iterator {
	public:
		/**** typedef ****/
		typedef T         				value_type;
		typedef Distance				difference_type;
		typedef Pointer					pointer;
		typedef const pointer			const_pointer;
		typedef Reference				reference;
		typedef const reference			const_reference;
		typedef Category  				iterator_category;
		typedef Iterator<Category, const T>	const_iterator;

	protected:
		/****	pointer to store the content ****/
		pointer	p;
	
	public:
		/**** constructor & destructor ****/
		Iterator(): p(NULL) {};
		Iterator(pointer p_src): p(p_src) {};
		Iterator(const Iterator& src): p(src.p) {};
		virtual ~Iterator() {};
		Iterator&	operator=(const Iterator& rhs) {
			p = rhs.p;
			return *this;
		};

		/**** operator - implicit conversion to const_iterator ****/
		operator const_iterator() const {
			return this->p;
		};


		/**** operator - prefix/postfix ++ ****/
		Iterator&			operator++() { 
			++p;
			return *this;
		};
		const Iterator	operator++(int) {
			const Iterator	old(*this);
			++p;
			return old;
		};

};

} /* end of namespace ft */

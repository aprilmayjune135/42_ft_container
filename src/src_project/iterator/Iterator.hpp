#pragma once
#include <cstddef>

namespace ft {

template <class T, class Category>
class Iterator {
	public:
		/**** typedef ****/
		typedef T         					value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef Category  					iterator_category;
		typedef Iterator<const T, Category>	const_iterator;

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

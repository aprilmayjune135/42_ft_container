#pragma once
#include "../iterator/iterator_traits.hpp"
#include "NodeAVL.hpp"

namespace AVL{

template <class T>
class NodeIterator {
	public:
	/**** member types ****/
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef const T*					const_pointer;
		typedef const T&					const_reference;
		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef NodeIterator<const T>		const_iterator;
		typedef NodeBase*					base_pointer;
		typedef Node<T>*					node_pointer;
	
	private:
		base_pointer	p;

	public:
	/**** constructor & destructor ****/
		NodeIterator(): p(NULL) {};
		NodeIterator(const NodeIterator& src) { *this = src; };
		NodeIterator(base_pointer p_src): p(p_src) {};
		~NodeIterator() {};

	/**** operator - equal ****/
		NodeIterator&	operator=(const NodeIterator& rhs) {
			this->p = rhs.p;
			return *this;
		};

	/**** operator - implicit conversion to const_iterator ****/
		operator const_iterator() const {
			return this->p;
		};

	/**** operator - non-member overload ****/
		friend bool	operator==(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.p == rhs.p; };
		friend bool	operator!=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.p != rhs.p; };

	/**** operator - dereference ****/
		reference		operator*() { return ((static_cast<node_pointer>(this->p))->value); };
		const_reference	operator*() const { return ((static_cast<node_pointer>(this->p))->value); };
		pointer			operator->() { return &((static_cast<node_pointer>(this->p))->value); };
		const_pointer	operator->() const { return &((static_cast<node_pointer>(this->p))->value); };

	/**** operator - prefix/postfix ++/-- ****/
		NodeIterator&	operator++() { 
			this->p = incrementNode(this->p);
			return *this;
		};
		const NodeIterator	operator++(int) {  // return const is to prevent behavior like ++++;
			const NodeIterator	old(*this);
			this->p = incrementNode(this->p);			
			return old;
		};
		NodeIterator&	operator--() { 
			this->p = decrementNode(this->p);
			return *this;
		};
		const NodeIterator	operator--(int) {
			const NodeIterator	old(*this);
			this->p = decrementNode(this->p);
			return old;
		};

};

} /* end of namespace ATL */

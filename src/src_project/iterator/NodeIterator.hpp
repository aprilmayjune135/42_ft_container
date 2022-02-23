#pragma once
#include "iterator_traits.hpp"
#include "BidrectionalIterator.hpp"
#include "../algorithm/NodeAVL.hpp"

namespace ft{

template <class T, class Category = bidirectional_iterator_tag>
class NodeIterator : public BidirectionalIterator<Category, T> {
	public:
	/**** member types ****/
		typedef T											pair_type;
		typedef Node<T>										node_type;
		typedef	BidirectionalIterator<node_type, Category>	base_iterator;
		typedef typename base_iterator::difference_type		difference_type;
		typedef typename base_iterator::pointer				pointer;
		typedef typename base_iterator::const_pointer		const_pointer;
		typedef typename base_iterator::reference			reference;
		typedef typename base_iterator::const_reference		const_reference;
		typedef typename base_iterator::iterator_category	iterator_category;
		typedef NodeIterator<const T>						const_iterator;
	
	/**** constructor & destructor ****/
		NodeIterator(): base_iterator() {};
		NodeIterator(const NodeIterator& src) { *this = src; };
		NodeIterator(pointer p_src): base_iterator(p_src) {};
		virtual ~NodeIterator() {};

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
		reference		operator*() { return *(this->p->value); };
		const_reference	operator*() const { return *(this->p->value); };
		pointer			operator->() { return this->p->value; };
		const_pointer	operator->() const { return this->p->value; };

	/**** operator - prefix/postfix ++/-- ****/
		NodeIterator&	operator++() { 
			++(this->p); // TODO: chante to tree.increment
			return *this;
		};
		const NodeIterator	operator++(int) {  // return const is to prevent behavior like ++++;
			const NodeIterator	old(*this);
			++(this->p); // TODO: chante to tree.increment
			return old;
		};
		NodeIterator&	operator--() { 
			--(this->p); // TODO: chante to tree.decrement
			return *this;
		};
		const NodeIterator	operator--(int) {
			const NodeIterator	old(*this);
			--(this->p); // TODO: chante to tree.decrement
			return old;
		};

};

} /* end of namespace ft */

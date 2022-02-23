#pragma once
#include "../pair/pair.hpp"
#include "../algorithm/TreeAVL.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include "../utility/print_tree.hpp" //TODO: to delete
#include <memory>
#include <iostream>

namespace ft {

namespace algorithm = AVL;

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
class map {
	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const key_type, mapped_type>		value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef BidirectionalIterator<value_type>		iterator;
		typedef BidirectionalIterator<const value_type>	const_iterator;
		typedef ReverseIterator<iterator>				reverse_iterator;
		typedef ReverseIterator<const_iterator>			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef std::size_t								size_type;
		typedef algorithm::Node<value_type>				node_type;

		class value_compare {
			friend class map;
			protected:
				Compare	comp;
				value_compare(Compare c): comp(c) {};
			public:
				typedef bool result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				};
		};

		typedef algorithm::Tree<value_type, value_compare, node_allocator_type> tree_type;


	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	private:
		key_compare				compare;
		allocator_type			allocator;
		tree_type				tree;
	
	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	public:
	// TODO: todelete
		void	print() const {
			utility::printNode(tree, NULL, false);
		};


	public:
	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
		/**** empty constructor ****/
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(value_comp()) {}; // TODO: what about alloc?

		/**** range constructor ****/
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(first, last, value_comp()) {};  // TODO: what about alloc?

		/**** copy constructor ****/
		map(const map& src):
			compare(src.compare),
			allocator(src.allocator),
			tree() {  // TODO: what about comp and alloc?
				*this = src;
		};

		/**** detructor ****/
		~map() {};

		/**** operator = ****/
		map&	operator=(const map& rhs) {
			//TODO
			return *this;
		};



	/*****************************************************/ 
	/**						iterator					**/ 
	/*****************************************************/
		iterator	begin() {
			return iterator(&(tree.minimum()->value));
		};

		const_iterator	begin() const {
			return const_iterator(&(tree.minimum()->value));
		};

		iterator	end() {
			return iterator(tree.maximum() + 1);
		};

		const_iterator	end() const {
			return const_iterator(tree.maximum() + 1);
		};

		reverse_iterator	rbegin() {
			return reverse_iterator(end());
		};

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		};

		reverse_iterator	rend() {
			return reverse_iterator(begin());
		};

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		};


	/*****************************************************/ 
	/**						capacity					**/ 
	/*****************************************************/
		bool	empty() const { return tree.empty(); };

		size_type	size() const { return  tree.size(); };

		size_type	max_size() const { 	return tree.max_size(); };

	/*****************************************************/ 
	/**					element access					**/ 
	/*****************************************************/


	/*****************************************************/ 
	/**						modifiers					**/ 
	/*****************************************************/
		/**** insert ****/
		pair<iterator, bool>	insert(const value_type& val) {
			algorithm::Node<value_type>*	new_node = createNode(val);
			tree = algorithm::insert<value_type>(tree, new_node);
			return make_pair<iterator, bool>(NULL, true); // TODO:: to add iterator
		};

		/**** clear ****/
		void clear() { tree.clear(); };
	

	/*****************************************************/ 
	/**						observer					**/ 
	/*****************************************************/
		key_compare		key_comp() const { return compare; };

		value_compare	value_comp() const { return value_compare(compare); };

	/*****************************************************/ 
	/**						allocator					**/ 
	/*****************************************************/


}; /* end of class map */


} /* end of namespace ft */

#pragma once
#include "../pair/pair.hpp"
#include "../algorithm/TreeAVL.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include <memory>
#include <iostream>
#include <functional>

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
		typedef std::size_t								size_type;

		class value_compare: public std::binary_function<value_type, value_type, bool> {
			friend class map;
			protected:
				Compare	comp;
				value_compare(Compare c): comp(c) {};
			public:
				typedef bool 		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				};
		};

		typedef algorithm::Node<value_type>				node_type;
		typedef algorithm::Tree<value_type, value_compare, allocator_type> tree_type;
		
		typedef	typename tree_type::iterator				iterator;
		typedef	typename tree_type::const_iterator			const_iterator;
		typedef	typename tree_type::reverse_iterator		reverse_iterator;
		typedef	typename tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;

	private:
		typedef	typename tree_type::pointer					node_pointer;
		typedef	typename tree_type::base_pointer			node_base_pointer;


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
	node_base_pointer	findNode(node_base_pointer node, const key_type& k) const {
		if (isEdge(node)) {
			return node;
		}
		if (compare(k, static_cast<node_pointer>(node)->value.first)) {
			return findNode(node->left, k);
		}
		else if (compare( static_cast<node_pointer>(node)->value.first, k)) {
			return findNode(node->right, k);
		}
		else {
			return node;
		}
	};

	public:
	// TODO: todelete
		void	print() const { tree.print(); };

	public:
	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
		/**** empty constructor ****/
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(value_comp(), allocator) {};

		/**** range constructor ****/
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(first, last, value_comp(), allocator) {};	

		/**** copy constructor ****/
		map(const map& src):
			compare(src.compare),
			allocator(src.allocator),
			tree(value_comp(), allocator) { *this = src; };

		/**** detructor ****/
		~map() {};

		/**** operator = ****/
		map&	operator=(const map& rhs) {
			tree = rhs.tree;
			return *this;
		};



	/*****************************************************/ 
	/**						iterator					**/ 
	/*****************************************************/
		iterator				begin() { return tree.begin(); };
		const_iterator			begin() const { return tree.begin(); };
		iterator				end() { return tree.end(); };
		const_iterator			end() const { return tree.end(); };
		reverse_iterator		rbegin() { return tree.rbegin(); };
		const_reverse_iterator	rbegin() const { return tree.rbegin(); };
		reverse_iterator		rend() { return tree.rend(); };
		const_reverse_iterator	rend() const { return tree.rend(); };

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
			iterator it = find(val.first);
			if (it != end()) {
				return ft::make_pair<iterator, bool>(it, false); 
			}
			return tree.insert(val);
		};

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last) {
			tree.insert(first, last);
		};

		/**** erase ****/
		void	erase(iterator position) {
			tree.erase(position);
		}

		size_type	erase(const key_type& k) {
			return tree.erase(find(k));
		}

		void	erase(iterator first, iterator last) {
			while (first != last) {
				iterator temp = first;
				++temp;
				tree.erase(first);
				first = temp;
			}
		}

		/**** clear ****/
		void clear() { tree.clear(); };
	

	/*****************************************************/ 
	/**						observer					**/ 
	/*****************************************************/
		key_compare		key_comp() const { return compare; };

		value_compare	value_comp() const { return value_compare(compare); };

	/*****************************************************/ 
	/**						operation					**/ 
	/*****************************************************/
		/**** find ****/
		iterator	find(const key_type& k) {
			node_base_pointer	node = findNode(tree.getRoot(), k);
			if (isEdge(node)) {
				return tree.end();
			}
			return iterator(node);
		};

		const_iterator	find(const key_type& k) const {
			node_base_pointer	node = findNode(tree.getRoot(), k);
			if (isEdge(node)) {
				return tree.end();
			}
			return const_iterator(node);
		};


	/*****************************************************/ 
	/**						allocator					**/ 
	/*****************************************************/
		allocator_type	get_allocator() const { return allocator; };

}; /* end of class map */


} /* end of namespace ft */

#pragma once
#include "../algorithm/TreeAVL.hpp"
#include "../algorithm/TreeRBT.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include <memory>
#include <iostream>
#include <functional>

namespace ft {

namespace algorithm_set = RBT; //choose between "AVL" or "RBT"

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set {
	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef T										key_type;
		typedef T										value_type;
		typedef Compare									key_compare;
		typedef Compare									value_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::size_t								size_type;

		typedef algorithm_set::Node<value_type>				node_type;
		typedef algorithm_set::Tree<value_type, value_compare, allocator_type> tree_type;
		
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

	public:
	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
		/**** empty constructor ****/
		explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(value_comp(), allocator) {};

		/**** range constructor ****/
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0):
			compare(comp),
			allocator(alloc),
			tree(first, last, value_comp(), allocator) {};	

		/**** copy constructor ****/
		set(const set& src):
			compare(src.compare),
			allocator(src.allocator),
			tree(value_comp(), allocator) { *this = src; };

		/**** detructor ****/
		~set() {};

		/**** operator = ****/
		set&	operator=(const set& rhs) {
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
	/**						modifiers					**/ 
	/*****************************************************/
		/**** insert ****/
		pair<iterator, bool>	insert(const value_type& val) {
			return tree.insert(val);
		};

		iterator	insert(iterator position, const value_type& val) {
			return tree.insert(position, val);
		}

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last, typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0) {
			return tree.insert(first, last);
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

		/**** swap ****/
		void	swap(set& x) {
			tree.swap(x.tree);
		};

		/**** clear ****/
		void	clear() { tree.clear(); };
	
	/*****************************************************/ 
	/**						observer					**/ 
	/*****************************************************/
		key_compare		key_comp() const { return compare; };

		value_compare	value_comp() const { return compare; };

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

		/**** count ****/
		size_type	count(const key_type& k) const {
			return !isEdge(findNode(tree.getRoot(), k));
		};

		/**** bound ****/
		iterator	lower_bound(const key_type& k) {
			return iterator(findLowerBound(tree.getRoot(), k));
		};

		const_iterator	lower_bound(const key_type& k) const {
			return const_iterator(findLowerBound(tree.getRoot(), k));
		};

		iterator	upper_bound(const key_type& k) {
			return iterator(findUpperBound(tree.getRoot(), k));
		};

		const_iterator	upper_bound(const key_type& k) const {
			return const_iterator(findUpperBound(tree.getRoot(), k));
		};

		pair<iterator, iterator>	equal_range(const key_type& k) {
			return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		};

		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const {
			return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		};

	/*****************************************************/ 
	/**						allocator					**/ 
	/*****************************************************/
		allocator_type	get_allocator() const { return allocator; };
	
	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
		node_base_pointer	findNode(node_base_pointer node, const key_type& k) const {
			if (isEdge(node)) {
				return node;
			}
			if (compare(k, static_cast<node_pointer>(node)->value)) {
				return findNode(node->left, k);
			}
			else if (compare( static_cast<node_pointer>(node)->value, k)) {
				return findNode(node->right, k);
			}
			else {
				return node;
			}
		};

		node_base_pointer	findLowerBound(node_base_pointer node, const key_type& k) const {
			if (compare(k, static_cast<node_pointer>(node)->value)) {
				if (!node->left) {
					return node;
				}
				return findLowerBound(node->left, k);
			}
			else if (compare(static_cast<node_pointer>(node)->value, k)) {
				if (isEdge(node->right)) {
					return incrementNode(node);
				}
				return findLowerBound(node->right, k);
			}
			else {
				return node;
			}
		};

		node_base_pointer	findUpperBound(node_base_pointer node, const key_type& k) const {
			if (compare(k, static_cast<node_pointer>(node)->value)) {
				if (!node->left) {
					return node;
				}
				return findUpperBound(node->left, k);
			}
			else if (compare(static_cast<node_pointer>(node)->value, k)) {
				if (isEdge(node->right)) {
					return incrementNode(node);
				}
				return findUpperBound(node->right, k);
			}
			else {
				return incrementNode(node);
			}
		};

}; /* end of class set */


} /* end of namespace ft */

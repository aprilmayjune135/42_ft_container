#pragma once
#include "../pair/pair.hpp"
#include "../algorithm/TreeRBT.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include <memory>
#include <iostream>
#include <functional>

namespace ft {

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
class map_temp {
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
			friend class map_temp;
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

		typedef RBT::Node<value_type>				node_type;
		typedef RBT::Tree<value_type, value_compare, allocator_type> tree_type;
		
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
		explicit map_temp(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			tree(value_comp(), allocator) {};

		/**** range constructor ****/
		template <class InputIterator>
		map_temp(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0):
			compare(comp),
			allocator(alloc),
			tree(first, last, value_comp(), allocator) {};	

		/**** copy constructor ****/
		map_temp(const map_temp& src):
			compare(src.compare),
			allocator(src.allocator),
			tree(value_comp(), allocator) { *this = src; };

		/**** detructor ****/
		~map_temp() {};

		/**** operator = ****/
		map_temp&	operator=(const map_temp& rhs) {
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
		mapped_type&	operator[] (const key_type& k) {
			return (*((insert(ft::make_pair<const Key, T>(k, mapped_type()))).first)).second;
		};

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
		void	swap(map_temp& x) {
			tree.swap(x.tree);
		};

		/**** clear ****/
		void	clear() { tree.clear(); };
	
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

		//TODO: to evaluate whether to directly use iterator++?
		node_base_pointer	findLowerBound(node_base_pointer node, const key_type& k) const {
			if (compare(k, static_cast<node_pointer>(node)->value.first)) {
				if (!node->left) {
					return node;
				}
				return findLowerBound(node->left, k);
			}
			else if (compare(static_cast<node_pointer>(node)->value.first, k)) {
				if (isEdge(node->right)) {
					return incrementNode(node);
				}
				return findLowerBound(node->right, k);
			}
			else {
				return node;
			}
		};

		//TODO: to evaluate whether to directly use iterator++?
		node_base_pointer	findUpperBound(node_base_pointer node, const key_type& k) const {
			if (compare(k, static_cast<node_pointer>(node)->value.first)) {
				if (!node->left) {
					return node;
				}
				return findUpperBound(node->left, k);
			}
			else if (compare(static_cast<node_pointer>(node)->value.first, k)) {
				if (isEdge(node->right)) {
					return incrementNode(node);
				}
				return findUpperBound(node->right, k);
			}
			else {
				return incrementNode(node);
			}
		};

	public:
		void	print() const { tree.print(); };


}; /* end of class map_temp */


} /* end of namespace ft */


void testMapTemp() {
	typedef	ft::pair<const int, char>	t_pair;
	typedef	ft::map_temp<int, char>	t_map;
	t_map	map;

	int	array[] = {33, 13, 53, 11, 21, 41, 61, 15, 31};
	std::size_t n = sizeof(array) / sizeof(int);
	for (std::size_t i = 0; i < n; ++i) {
		t_pair	pair(array[i], 'a' + array[i] % 26);
		map.insert(pair);
	}
	map.print();

}

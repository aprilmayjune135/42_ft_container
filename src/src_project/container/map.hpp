#pragma once
#include "../pair/pair.hpp"
#include "../algorithm/NodeAVL.hpp"
#include "../iterator/BidirectionalIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../iterator/lexicographic_compare.hpp"
#include "../utility/print_tree.hpp" //TODO: to delete
#include <memory>
#include <iostream>

namespace ft {

namespace algorithm = AVL;

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
class map {
	public:

	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
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
		typedef typename Alloc::template rebind<node_type>::other node_allocator_type;

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



	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	private:
		key_compare						compare;
		allocator_type					allocator;
		node_allocator_type				node_allocator;
		algorithm::Node<value_type>*	root;
		size_type						data_size;
	
	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	public:
	// TODO: todelete
		void	print() const {
			utility::printNode(root, NULL, false);
		};
	
	private:
		node_type*	createNode(const value_type& val) {
			node_type	node_value(val);
			node_type*	new_node = node_allocator.allocate(1);
			node_allocator.construct(new_node, node_value);
			data_size++;
			return new_node;
		};

		void		deleteNode(node_type* node) {
			if (node) {
				deleteNode(node->left);
				deleteNode(node->right);
				node_allocator.destroy(node);
				node_allocator.deallocate(node, 1);
				data_size--;
			}
		}


	public:
	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
		/**** empty constructor ****/
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			root(NULL),
			data_size(0) {};

		/**** range constructor ****/
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			root(NULL),
			data_size(0) {
				// TODO
		};


		/**** copy constructor ****/
		map(const map& src):
			compare(src.compare),
			allocator(src.allocator),
			root(NULL),
			data_size(0) {
				*this = src;
		};


		/**** detructor ****/
		~map() {
			deleteNode(root);
		};

		/**** operator = ****/
		map&	operator=(const map& rhs) {
			//TODO
			return *this;
		};



	/*****************************************************/ 
	/**						iterator					**/ 
	/*****************************************************/


	/*****************************************************/ 
	/**						capacity					**/ 
	/*****************************************************/
		bool	empty() const { return data_size == 0; };

		size_type	size() const { return data_size; };

		size_type	max_size() const { 	return allocator.max_size(); }; //TODO: node_allocator???

	/*****************************************************/ 
	/**					element access					**/ 
	/*****************************************************/


	/*****************************************************/ 
	/**						modifiers					**/ 
	/*****************************************************/
		/**** insert ****/
		pair<iterator, bool>	insert(const value_type& val) {
			algorithm::Node<value_type>*	new_node = createNode(val);
			root = algorithm::insert<value_type>(root, new_node);
			return make_pair<iterator, bool>(NULL, true);
		};

		/**** clear ****/
		void clear() { deleteNode(root); };
	

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

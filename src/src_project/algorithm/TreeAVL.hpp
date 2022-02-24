#pragma once
#include "NodeIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../pair/pair.hpp"
#include "../utility/print_tree.hpp" //TODO: to delete

#include <memory>

namespace AVL {

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class Tree {

	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef Tree<T, Compare, Alloc>				tree_type;
		typedef	T									value_type;
		typedef Node<value_type>					node_type;
		typedef node_type*							pointer;
		typedef NodeBase*							base_pointer;
		typedef NodeIterator<value_type>			iterator;
		typedef typename iterator::const_iterator	const_iterator;
		typedef ft::ReverseIterator<iterator>		reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>	const_reverse_iterator;
		typedef std::size_t							size_type;
		typedef Compare								compare_type;
		typedef Alloc								value_allocator_type;
		typedef typename Alloc::template rebind<node_type>::other allocator_type;

	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	private:
		compare_type	value_compare;
		allocator_type	allocator;
		NodeBase		sentinel;
		base_pointer	root;
		size_type		tree_size;

	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	private:
		base_pointer	createNode(const value_type& val) {
			pointer	new_node = allocator.allocate(1);
			node_type	node_value(&sentinel, val);
			allocator.construct(new_node, node_value);
			tree_size++;
			return new_node;
		};

		void	deleteNode(base_pointer node) {
			if (!isSentinel(node)) {
				deleteNode(node->left);
				deleteNode(node->right);
				allocator.destroy(static_cast<pointer>(node));
				allocator.deallocate(static_cast<pointer>(node), 1);
				tree_size--;
			}
		};
	public: //TODO: to delete
		void	print() const {
			utility::printNode<T>(root, NULL, false);
		};

	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
	public:
		/**** empty constructor ****/
		explicit Tree(const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			value_compare(comp),
			allocator(alloc),
			sentinel(&sentinel, 0),
			root(&sentinel),
			tree_size(0) {};

		/**** range constructor ****/
		template <class InputIterator>
		Tree(InputIterator first, InputIterator last, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			value_compare(comp),
			allocator(alloc),
			sentinel(&sentinel, 0),
			root(&sentinel),
			tree_size (0) {
				// TODO
		};


		/**** copy constructor ****/
		Tree(const tree_type& src):
			value_compare(src.comp),
			allocator(src.alloc),
			sentinel(&sentinel, 0),
			root(&sentinel),
			tree_size(0) {
				*this = src;
		};
		
		~Tree() {
			deleteNode(root);
		};

		tree_type&	operator=(const tree_type& rhs) {
			//TODO:
		};

		//TODO: to evaluate
		const pointer	getRoot() const { return static_cast<pointer>(root); };

	/*****************************************************/ 
	/**						iterator					**/ 
	/*****************************************************/
		iterator	begin() {
			return iterator(minimumNode(root));
		};

		const_iterator	begin() const {
			return const_iterator(minimumNode(root));
		};

		iterator	end() {
			return iterator(&sentinel);
		};

		const_iterator	end() const {
			return const_iterator(&sentinel);
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
	/**					member function					**/ 
	/*****************************************************/
		bool	empty() const { return tree_size == 0; };
		
		size_type	size() const { return tree_size; };

		size_type	max_size() const { 	return allocator.max_size(); };

		ft::pair<iterator, bool>	insert(const value_type& value) {
			if (false) {
				// TODO: to add if pair key already exist; return current node
				return make_pair(iterator(NULL), false);
			}
			else {
				base_pointer	new_node = createNode(value);
				root = insertNode<T>(root, new_node);
				return make_pair(iterator(new_node), true);
			}
		};

		void clear() { deleteNode(root); };
};

} /* end of namespace AVL */

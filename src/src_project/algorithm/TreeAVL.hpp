#pragma once
#include "NodeAVL.hpp"
#include "iterator_traits.hpp"
#include "../pair/pair.hpp"

#include <memory>
#define BALANCE_MIN -1
#define BALANCE_MAX 1

namespace AVL {

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class Tree {
	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef Tree<T, Compare, Alloc>		tree_type;
		typedef	T					value_type;
		typedef Node<value_type>	node_type;
		typedef node_type*			node_pointer;
		typedef const node_type*	const_node_pointer;
		typedef node_type&			node_reference;
		typedef const ndoe_type&	const_node_reference;
		typedef std::size_t			size_type;
		typedef Compare				compare_type;
		typedef Alloc				value_allocator_type;
		typedef typename Alloc::template rebind<node_type>::other allocator_type;

	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	private:
		compare_type	value_compare;
		allocaotor_type	allocator;
		pointer			root;
		size_type		tree_size;

	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	private:
		node_type*	createNode(const value_type& val) {
			node_type*	new_node = allocator.allocate(1);
			node_type	node_value(val);
			allocator.construct(new_node, node_value);
			tree_size++;
			return new_node;
		};

		void	deleteNode(node_type* node) {
			if (node) {
				deleteNode(node->left);
				deleteNode(node->right);
				allocator.destroy(node);
				allocator.deallocate(node, 1);
				tree_size--;
			}
		};


	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
	public:
		/**** empty constructor ****/
		explicit Tree(const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			value_compare(comp),
			allocator(alloc),
			root(NULL),
			tree_size(0) {};

		/**** range constructor ****/
		template <class InputIterator>
		Tree(InputIterator first, InputIterator last, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type():
			value_compare(comp),
			allocator(alloc) {
				// TODO
		};


		/**** copy constructor ****/
		Tree(const tree_type& src):
			value_compare(src.comp),
			allocator(src.alloc),
			root(NULL),
			tree_size(0) {
				*this = src;
		};
		
		~Tree() {
			deleteNode(root);
		};

		tree_type&	operator=(const tree_type& rhs) {
			//TODO:
		};

	/*****************************************************/ 
	/**					member function					**/ 
	/*****************************************************/
		bool	empty() const { return tree_size == 0; };
		
		size_type	size() const { return tree_size; };

		size_type	max_size() const { 	return allocator.max_size(); };

		pair<pointer, bool>	insert(const value_type& value) {
			if (false) {
				// TODO: to add if pair key already exist; return current node
				return make_pair(NULL, false);
			}
			else {
				pointer	new_node = createNode(value);
				root = insertNode(root, new_node);
				return make_pair(new_node, true);
			}
		};

		void clear() { deleteNode(root); };

		pointer	increment(pointer node) {
			if (!node) {
				return NULL;
			}
			if (node->right) {
				node = node->right;
				while (node) {
					node = node->left;
				}
				return node;
			}
			else {
				pointer temp = root;
				while (temp != node) {
					if (value_compare()(node->value, temp->value) {
						if (temp->left == node) {
							return temp;
						}
						if (maximum(temp->left) == node) {
							return temp;
						}
						temp = temp->left;
					}
					else {
						temp = temp->right;
					}
				}
				return node + 1;
			}
		};

		pointer	decrement(pointer node) {
			if (!node) {
				return NULL;
			}
			if (node->left) {
				node = node->left;
				while (node) {
					node = node->right;
				}
				return node;
			}
			else {
				pointer temp = root;
				while (temp != node) {
					if (value_compare()(temp->value, node->value) {
						if (temp->right == node) {
							return temp;
						}
						if (minimum(temp->right) == node) {
							return temp;
						}
						temp = temp->right;
					}
					else {
						temp = temp->left;
					}
				}
				return node - 1;
			}
		};


	/*****************************************************/ 
	/**						min & max					**/ 
	/*****************************************************/
		pointer	minimum(pointer root) {
			while (root && root->height > 1) {
				root = root->left;
			}
			return root;
		}

		const_pointer	minimum(const_pointer root) {
			while (root && root->height > 1) {
				root = root->left;
			}
			return root;
		}

		pointer	maximum(pointer root) {
			while (root && root->height > 1) {
				root = root->right;
			}
			return root;
		}

		const_pointer	maximum(const_pointer root) {
			while (root && root->height > 1) {
				root = root->right;
			}
			return root;
		}


};

} /* end of namespace AVL */

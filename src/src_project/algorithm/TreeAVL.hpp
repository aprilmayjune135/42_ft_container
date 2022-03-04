#pragma once
#include "NodeIterator.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../pair/pair.hpp"
#include "../utility/print_tree.hpp" //TODO: to delete

#include <memory>

namespace AVL {

template <class T, class Compare, class Alloc>
class Tree {

	/*****************************************************/ 
	/**					member types					**/ 
	/*****************************************************/
	public:
		typedef Tree<T, Compare, Alloc>					tree_type;
		typedef	T										value_type;
		typedef Node<value_type>						node_type;
		typedef node_type*								pointer;
		typedef NodeBase*								base_pointer;
		typedef NodeIterator<value_type>				iterator;
		typedef typename iterator::const_iterator		const_iterator;
		typedef ft::ReverseIterator<iterator>			reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>		const_reverse_iterator;
		typedef std::size_t								size_type;
		typedef Compare									compare_type;
		typedef Alloc									allocator_type;
		typedef typename Alloc::template rebind<node_type>::other	node_allocator_type;

	/*****************************************************/ 
	/**					key members						**/ 
	/*****************************************************/
	private:
		compare_type		compare;
		allocator_type		allocator;
		NodeBase			sentinel;
		base_pointer		root;
		size_type			tree_size;

	/*****************************************************/ 
	/**				private member function				**/ 
	/*****************************************************/
	private:
		pointer	createNode(const value_type& val) {
			node_type	node_value(NULL, &sentinel, val);
			node_allocator_type	node_allocator;
			pointer	new_node = node_allocator.allocate(1); //TODO: throw exception?
			node_allocator.construct(new_node, node_value);
			tree_size++;
			return new_node;
		};

		void	removeNode(pointer node) {
			node_allocator_type	node_allocator;
			node_allocator.destroy(node); //TODO: throw exception? note clear() has no-throw gaurantee
			node_allocator.deallocate(node, 1);
			node = NULL;
			tree_size--;
		}

		base_pointer	rebalanceInsertNode(base_pointer node, const value_type& val) {
			int balance_factor = getBalance(node);
			if (isLeftHeavy(balance_factor) && compare(val, static_cast<pointer>(node->left)->value)) {
				return rightRotate(node);
			}
			else if (isLeftHeavy(balance_factor) && compare(static_cast<pointer>(node->left)->value, val)) {
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
			else if (isRightHeavy(balance_factor) && compare(static_cast<pointer>(node->right)->value, val)) {
				return leftRotate(node);
			}
			else if (isRightHeavy(balance_factor) && compare(val, static_cast<pointer>(node->right)->value)) {
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			else {
				return node;
			}
		};
	
		base_pointer	insertNode(base_pointer node, pointer new_node) {
			if (!node) {
				return new_node;
			}
			if (isSentinel(node)) {
				sentinel.parent = new_node;
				new_node->right = &sentinel;
				return new_node;
			}
			if (compare(new_node->value, static_cast< pointer >(node)->value)) {
				node->left = insertNode(node->left, new_node);
				node->left->parent = node; //TODO: to evaluate efficiency: check if node->left->parent == NULL first?
			}
			else if (compare(static_cast< pointer >(node)->value, new_node->value)) {
				if (node->right == &sentinel) {
					new_node->right = &sentinel;
					sentinel.parent = new_node;
					node->right = NULL;
				}
				node->right = insertNode(node->right, new_node);
				node->right->parent = node;
			}
			else {
				return node; // do nothing if node is already exist;
			}
			updateHeight(node);
			return rebalanceInsertNode(node, new_node->value);
		};

		base_pointer	rebalanceDeleteNode(base_pointer node) {
			int balance_factor = getBalance(node);
			if (isLeftHeavy(balance_factor)) {
				if (getBalance(node->left) >= 0) {
					return rightRotate(node);
				}
				else {
					node->left = leftRotate(node->left);
					return rightRotate(node);
				}
			}
			else if (isRightHeavy(balance_factor)) {
				if (getBalance(node->right) <= 0) {
					return leftRotate(node);
				}
				else {
					node->right = rightRotate(node->right);
					return leftRotate(node);
				}
			}
			else {
				return node;
			}
		}

		base_pointer	deleteNode(base_pointer node, const value_type& val) {
			if (isEdge(node)) {
				return node;
			}
			if (compare(val, static_cast< pointer >(node)->value)) {
				node->left = deleteNode(node->left, val);
			}
			else if (compare(static_cast< pointer >(node)->value, val)) {
				node->right = deleteNode(node->right, val);
			}
			else {
				if (node->height == 1) {
					if (isSentinel(node->right)) {
						sentinel.parent = node->parent;
					}
					base_pointer	temp = node->right;
					removeNode(static_cast<pointer>(node));
					return temp;
				}
				else if (isEdge(node->left) || isEdge(node->right)) {
					base_pointer	temp = node->left ? node->left : node->right;
					if (isSentinel(node->right)) {
						temp->right = node->right;
						sentinel.parent = temp;
					}
					temp->parent = node->parent;
					removeNode(static_cast<pointer>(node));
					return temp;
				}
				else {
					base_pointer	temp = incrementNode(node);
					*static_cast<pointer>(node) = *static_cast<pointer>(node);
					return node;
				}
			}
			updateHeight(node);
			return rebalanceDeleteNode(node);
		}

		void	insertTree(base_pointer node) {
			if (isEdge(node)) {
				return ;
			}
			insert(static_cast< pointer >(node)->value);
			insertTree(node->left);
			insertTree(node->right);
		}

		void	clearTree(base_pointer node) {
			if (!isEdge(node)) {
				clearTree(node->left);
				clearTree(node->right);
				removeNode(static_cast<pointer>(node));
			}
		};

	/*****************************************************/ 
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
	public:
		/**** empty constructor ****/
		explicit Tree(const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			sentinel(&sentinel, &sentinel, 0),
			root(&sentinel),
			tree_size(0) {};

		/**** range constructor ****/
		template <class InputIterator>
		Tree(InputIterator first, InputIterator last, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			sentinel(&sentinel, &sentinel, 0),
			root(&sentinel),
			tree_size (0) { insert<InputIterator>(first, last); };

		/**** copy constructor ****/ //TODO: is this needed?
		// Tree(const tree_type& src):
		// 	compare(src.comp),
		// 	allocator(src.alloc),
		// 	sentinel(&sentinel, &sentinel, 0),
		// 	root(&sentinel),
		// 	tree_size(0) {
		// 		*this = src;
		// };
		
		~Tree() {
			clearTree(root);
		};

		tree_type&	operator=(const tree_type& rhs) {
			clear();
			insertTree(rhs.root);
			return *this;
		};

		//TODO: to evaluate
		base_pointer	getRoot() const { return root; };

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
			pointer	new_node = createNode(value);
			root = insertNode(root, new_node);
			return ft::make_pair<iterator, bool>(iterator(new_node), true);
		};

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				++first;
			}
		};

		size_type	erase(iterator position) {
			if (position == end()) {
				return 0;
			}
			else {
				root = deleteNode(root, *position);
				return 1;				
			}
		};

		void clear() {
			clearTree(root);
			sentinel.parent = &sentinel;
		};

	/*****************************************************/ 
	/**					public utility					**/ 
	/*****************************************************/
	public:
		void	print() const {
			utility::printNode<value_type>(root, NULL, false);
		};

}; /* end of class TreeAVL */

} /* end of namespace AVL */

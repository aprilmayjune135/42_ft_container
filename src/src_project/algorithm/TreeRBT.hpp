#pragma once
#include "NodeIteratorRBT.hpp"
#include "../iterator/ReverseIterator.hpp"
#include "../pair/pair.hpp"
#include "../utility/print_tree.hpp" //TODO: to delete

#include <memory>
#include <algorithm>

namespace RBT {

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
	/**			constructor	& destructor & operator		**/ 
	/*****************************************************/
	public:
		/**** empty constructor ****/
		explicit Tree(const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type()):
			compare(comp),
			allocator(alloc),
			sentinel(&sentinel, &sentinel, RBT_BLACK),
			root(&sentinel),
			tree_size(0) {};

		/**** range constructor ****/
		template <class InputIterator>
		Tree(InputIterator first, InputIterator last, const compare_type& comp = compare_type(), const allocator_type& alloc = allocator_type(), typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0):
			compare(comp),
			allocator(alloc),
			sentinel(&sentinel, &sentinel, RBT_BLACK),
			root(&sentinel),
			tree_size (0) { insert<InputIterator>(first, last); };

		~Tree() {
			clear();
		};

		tree_type&	operator=(const tree_type& rhs) {
			clear();
			insertTree(rhs.root);
			return *this;
		};

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
			return const_iterator(const_cast<base_pointer>(&sentinel));
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

		ft::pair<iterator, bool>	insert(const value_type& val) {
			iterator	it = find(val);
			if (it != end()) {
				return ft::make_pair<iterator, bool>(it, false);
			}
			else {
				pointer	new_node = createNode(val);
				root = insertNode(root, new_node);
				recolorInsertNode(new_node);
				return ft::make_pair<iterator, bool>(iterator(new_node), true);
			}			
		};

		//TODO: to implement for position (lower/upper bound???)
		iterator	insert(iterator position, const value_type& val) {
			iterator	it = find(val);
			if (it != end()) {
				return it;
			}
			else {
				pointer	new_node = createNode(val);
				root = insertNode(root, new_node);
				recolorInsertNode(new_node);
				return iterator(new_node);
			}
		}

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last, typename ft::iterator_traits<InputIterator>::iterator_category* dummy = 0) {
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
				deleteNode(root, *position);
				return 1;	
			}
		};

		void	swap(tree_type& x) {
			swapPointer(root->parent, x.root->parent, &sentinel, &(x.sentinel));
			swapPointer(root, x.root, &sentinel, &(x.sentinel));
			swapPointer(sentinel.parent, x.sentinel.parent, &sentinel, &(x.sentinel));
			swapPointer(sentinel.parent->right, x.sentinel.parent->right, &sentinel, &(x.sentinel));
			
			std::swap(tree_size, x.tree_size);
		}

		void	clear() {
			clearTree(root);
			sentinel.parent = &sentinel;
			root = &sentinel;
		};

		iterator	find(const value_type& val) {
			base_pointer	node = findNode(root, val);
			if (isEdge(node)) {
				return end();
			}
			return iterator(node);
		}

		const_iterator	find(const value_type& val) const {
			base_pointer	node = findNode(root, val);
			if (isEdge(node)) {
				return end();
			}
			return const_iterator(node);
		}

	/*****************************************************/ 
	/**					public utility					**/ 
	/*****************************************************/
	public:
		void	print() const {
			utility::printNode<value_type>(root, NULL, false);
		};

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


		base_pointer	findNode(base_pointer node, const value_type& val) const {
			if (isEdge(node)) {
				return node;
			}
			if (compare(val, static_cast<pointer>(node)->value)) {
				return findNode(node->left, val);
			}
			else if (compare( static_cast<pointer>(node)->value, val)) {
				return findNode(node->right, val);
			}
			else {
				return node;
			}
		};	

		void	rightRotate(base_pointer x) {
			base_pointer y = x->left;
			y->parent = x->parent;
			x->left = y->right;
			if (!isEdge(x->left)) {
				x->left->parent = x;
			}
			if (isSentinel(x->parent)) {
				root = y;
			}			
			else if (isLeftChild(x)) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
			y->right = x;
			x->parent = y;
		}

		void	leftRotate(base_pointer x) {
			base_pointer y = x->right;
			y->parent = x->parent;
			x->right = y->left;
			if (!isEdge(x->right)) {
				x->right->parent = x;
			}
			if (isSentinel(x->parent)) {
				root = y;
			}			
			else if (isLeftChild(x)) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void	recolorInsertNode(base_pointer node) {
			// scenario 2: Parent is black => do nothing
			// scenario 3: Parent is red (proof of Grandparent exists (because root cannot be red), and Grandparent has to be black (cannot be two red together))
			while (node != root && isRed(node->parent)) {
				// scenario 3.1: Parent is red, Uncle is red
				base_pointer	uncle = getUncle(node);
				if (isRed(uncle)) {
					node->parent->parent->color = RBT_RED;
					node->parent->color = RBT_BLACK;
					uncle->color = RBT_BLACK;
					node = node->parent->parent;
				}
				// scenario 3.2: Parent is red, Uncle is black
				else {
					if (isRightChild(node->parent)) {
						// scenario 3.2.2: Parent is right child and Node is left child
						if (isLeftChild(node)) {
							node = node->parent;
							rightRotate(node);
						}
						// scenario 3.2.1: Parent is right child and Node is right child
						node->parent->parent->color = RBT_RED;
						node->parent->color = RBT_BLACK;
						leftRotate(node->parent->parent);
					}
					else {
						// scenario 3.2.4: Parent is left child and Node is right child
						if (isRightChild(node)) {
							node = node->parent;
							leftRotate(node);
						}
						// scenario 3.2.3: Parent is left child and Node is left child
						node->parent->parent->color = RBT_RED;
						node->parent->color = RBT_BLACK;
						rightRotate(node->parent->parent);
					}
				}
			}
			// scenario 1: node is the root
			if (node == root) {
				node->color = RBT_BLACK;
			}
		};

		/* assume new_node is not an existing value */
		base_pointer	insertNode(base_pointer node, pointer new_node) {
			if (isEdge(node)) {
				if (isSentinel(node)) {
					sentinel.parent = new_node;
					new_node->right = &sentinel;
				}
				return new_node;
			}
			if (compare(new_node->value, static_cast< pointer >(node)->value)) {
				node->left = insertNode(node->left, new_node);
				node->left->parent = node;
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
			return node;
		};

		/*
		- assume node is already found in the tree, it cannot be Edge node, and it is either leaf or has only one child.
		- incase of rotate involves root, the root will be changed in deleteNode() function;
		*/
		void	recolorDeleteNode(base_pointer node) {
			// scenario 1: node is red -> deleting a red node does not violate any rule.
			if (isRed(node)) {
				return ;
			}
			// scenario 2: node is black and has one red child -> child turn to black (node will be future replaced by this child)
			base_pointer child = node->left ? node->left : node->right;
			if (isRed(child)) {
				child->color = RBT_BLACK;
				return ;
			}
			// scenario 3: node is black and is a leaf or has one black child
			while (node != root && node->color == RBT_BLACK) {
				if (isLeftChild(node)) {
					base_pointer sibling = node->parent->right;
					// scenario 3.1 Sibling is red -> rotate to make Sibling black to meet scenario 3.2
					if (isRed(sibling)) {
						std::swap(node->parent->color, sibling->color);
						leftRotate(node->parent);
						sibling = node->parent->right;
					}
					// scenario 3.2 Sibling is black, and both of Sibling's children are black
					if (isBlack(sibling->left) && isBlack(sibling->right)) {
						sibling->color = RBT_RED;
						node = node->parent;
					}
					else {
						// scenario 3.3 Sibling is black, Sibling's left child is red, right child is black -> rotate to meet scenario 3.4
						if (isBlack(sibling->right)) {
							std::swap(sibling->color, sibling->left->color);
							rightRotate(sibling);
							sibling = node->parent->right;
						}
						// scenario 3.4 Sibling is black, Sibling's right child is red
						sibling->color = node->parent->color;
						node->parent->color = RBT_BLACK;
						sibling->right->color = RBT_BLACK;
						leftRotate(node->parent);
						node = root;
					}
				}
				else {
					base_pointer sibling = node->parent->left;
					// scenario 3.1 Sibling is red -> rotate to make Sibling black to meet scenario 3.2
					if (isRed(sibling)) {
						std::swap(node->parent->color, sibling->color);
						rightRotate(node->parent);
						sibling = node->parent->left;
					}
					// scenario 3.2 Sibling is black, and both of Sibling's children are black
					if (isBlack(sibling->left) && isBlack(sibling->right)) {
						sibling->color = RBT_RED;
						node = node->parent;
					}
					else {
						// scenario 3.3 Sibling is black, Sibling's left child is red, right child is black -> rotate to meet scenario 3.4
						if (isBlack(sibling->left)) {
							std::swap(sibling->color, sibling->right->color);
							leftRotate(sibling);
							sibling = node->parent->left;
						}
						// scenario 3.4 Sibling is black, Sibling's right child is red
						sibling->color = node->parent->color;
						node->parent->color = RBT_BLACK;
						sibling->left->color = RBT_BLACK;
						rightRotate(node->parent);
						node = root;
					}
				}		
			}
			node->color = RBT_BLACK;
		}

		void	swapNode(base_pointer x, base_pointer y) {
			// swap parent
			if (x->parent->left == x) {
				x->parent->left = y;
			}
			else if (x->parent->right == x) {
				x->parent->right = y;
			}
			if (y->parent->left == y) {
				y->parent->left = x;
			}
			else if (y->parent->right == y) {
				y->parent->right = x;
			}
			std::swap(x->parent, y->parent);

			// swap left
			x->left->parent = y;
			if (y->left) {
				y->left->parent = x;
			}			
			std::swap(x->left, y->left);

			// swap right
			x->right->parent = y;
			if (y->right) {
				y->right->parent = x;
			}		
			std::swap(x->right, y->right);

			// swap color
			std::swap(x->color, y->color);

			// swap root
			if (root == x) {
				root = y;
			}
			else if (root == y) {
				root = x;
			}
		}

		/* return the node to be deleted and convert it to leaf or node with only one child */
		base_pointer	deleteNodeLocator(base_pointer node, const value_type& val) {
			if (isEdge(node)) {
				return node;
			}
			if (compare(val, static_cast< pointer >(node)->value)) {
				return deleteNodeLocator(node->left, val);
			}
			else if (compare(static_cast< pointer >(node)->value, val)) {
				return deleteNodeLocator(node->right, val);
			}
			else if (!isEdge(node->left) && !isEdge(node->right)) {
				base_pointer	temp = incrementNode(node);
				swapNode(node, temp);
				return deleteNodeLocator(temp->right, static_cast<pointer>(node)->value);
			}
			return node;
		}

		void	deleteNode(base_pointer root_node, const value_type& val) {
			base_pointer	node = deleteNodeLocator(root_node, val);
			recolorDeleteNode(node);
			// take care of root
			if (node == root) {
				root = (node->left ? node->left : node->right);
			}
			else {
				// take care of parent
				if (isRightChild(node)) {
					node->parent->right = node->right;
				}
				else {
					node->parent->left = node->left;
				}
			}
			// scenario 1: leaf node
			if (isEdge(node->left) && isEdge(node->right)) {
				if (isSentinel(node->right)) {
					sentinel.parent = node->parent;
				}
				removeNode(static_cast<pointer>(node));
			}
			// scenario 2: has 1 child node
			else if (isEdge(node->left) || isEdge(node->right)) {
				base_pointer temp = node->left ? node->left : node->right;
				if (isSentinel(node->right)) {
					temp->right = node->right;
					sentinel.parent = temp;
				}
				temp->parent = node->parent;
				removeNode(static_cast<pointer>(node));
			}
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

		void	swapPointer(base_pointer& x1, base_pointer& x2, base_pointer s1, base_pointer s2) {
			if (x1 == s1) {
				if (x2 == s2) {
					return ;
				}
				else {
					x1 = x2;
					x2 = s2;
				}
			}
			else {
				if (x2 == s2) {
					x2 = x1;
					x1 = s1;
				}
				else {
					std::swap(x1, x2);
				}
			}
		}


}; /* end of class TreeRBT */

} /* end of namespace RBT */

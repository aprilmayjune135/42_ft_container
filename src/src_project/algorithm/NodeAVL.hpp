#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#define BALANCE_MIN -1
#define BALANCE_MAX 1

namespace AVL {

struct NodeBase {

};

template <class T>
struct Node {
	Node<T>*	left;
	Node<T>*	right;
	Node<T>*	parent;
	T			value;
	int			height;
	Node(const T& src): left(NULL), right(NULL), parent(NULL), value(src), height(1) {};
};

template <class T>
int	height(Node<T>* node) {
	if (!node) {
		return 0;
	}
	return node->height;
}

template <class T>
int	getBalance(Node<T>* node) {
	return height(node->left) - height(node->right);
}

template <class T>
void	updateHeight(Node<T>* node) {
	node->height = std::max(height(node->left), height(node->right)) + 1;
}

template <class T>
Node<T>* 	minimumNode(Node<T>*  node) {
	while (node && node->height > 1) {
		node = node->left;
	}
	return node;
}

template <class T>
const Node<T>* 	minimumNode(const Node<T>*  node) {
	while (node && node->height > 1) {
		node = node->left;
	}
	return node;
}

template <class T>
Node<T>* 	maximumNode(Node<T>*  node) {
	while (node && node->height > 1) {
		node = node->right;
	}
	return node;
}

template <class T>
const Node<T>* 	maximumNode(const Node<T>*  node) {
	while (node && node->height > 1) {
		node = node->right;
	}
	return node;
}

template <class T>
Node<T>*	rightRotate(Node<T>* x) {
	Node<T>* y = x->left;
	y->parent = x->parent;
	x->left = y->right;
	if (x->left) {
		x->left->parent = x;
	}
	y->right = x;
	x->parent = y;
	updateHeight(x);
	updateHeight(y);
	return y;
}

template <class T>
Node<T>*	leftRotate(Node<T>* x) {
	Node<T>* y = x->right;
	y->parent = x->parent;
	x->right = y->left;
	if (x->right) {
		x->right->parent = x;
	}
	y->left = x;
	x->parent = y;
	updateHeight(x);
	updateHeight(y);
	return y;
}

template <class T>
Node<T>*	balanceNode(Node<T>* node,Node<T>* new_node) {
	int balance_factor = getBalance(node);
	if (balance_factor > BALANCE_MAX && new_node->value < node->left->value) { // TODO: to add value_compare
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && node->right->value < new_node->value) { // TODO: to add value_compare
		return leftRotate(node);
	}
	else if (balance_factor > BALANCE_MAX && node->left->value < new_node->value ) { // TODO: to add value_compare
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && new_node->value < node->right->value) { // TODO: to add value_compare
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	else {
		return node;
	}

}

/* do nothing if node already exists */
template <class T>
Node<T>*	insertNode(Node<T>* node, Node<T>* new_node) {
	if (!node) {
		return new_node;
	}
	if (!new_node) {
		return node;
	}
	if (new_node->value < node->value) { // TODO: to add value_compare
		node->left = insertNode(node->left, new_node);
		node->left->parent = node; //TODO: to evaluate efficiency: check if node->left->parent == NULL first?
	}
	else if (node->value < new_node->value) { 
		node->right = insertNode(node->right, new_node);
		node->right->parent = node;
	}
	else {
		return node; // do nothing if node is already exist;
	}
	updateHeight(node);
	return balanceNode(node, new_node);
}

template <class T>
Node<T>*	incrementNode(Node<T>* node) {
	if (!node) {
		return NULL;
	}
	if (node->right) {
		node = node->right;
		while (node->left) {
			node = node->left;
		}
		return node;
	}
	else {
		Node<T>* temp = node->parent;
		while (temp && node == temp->right) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}


template <class T>
Node<T>*	decrementNode(Node<T>* node) {
	if (!node) {
		return NULL;
	}
	if (node->left) {
		node = node->left;
		while (node->right) {
			node = node->right;
		}
		return node;
	}
	else {
		Node<T>* temp = node->parent;
		while (temp && node == temp->left) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

//TODO: to delete?
// template <class T>
// Node<T>*	treeSearch(Node<T>* node, const T& value) {
// 	if (!node || value == node->value) {
// 		return node;
// 	}
// 	if (value < node->value) {
// 		return treeSearch(node->left, value);
// 	}
// 	return treeSearch(node->right, value);
// }

} /* end of namespace AVL */

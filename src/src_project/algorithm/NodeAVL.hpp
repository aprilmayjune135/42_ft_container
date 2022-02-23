#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#define BALANCE_MIN -1
#define BALANCE_MAX 1

namespace AVL {

template <class T>
struct Node {
	Node<T>*	left;
	Node<T>*	right;
	T			value;
	int			height;
	Node(const T& src): left(NULL), right(NULL), value(src), height(1) {};
};

template <class T>
int	height(Node<T>*	node) {
	if (!node) {
		return 0;
	}
	return node->height;
}

template <class T>
int	getBalance(Node<T>*	node) {
	return height(node->left) - height(node->right);
}

template <class T>
void	updateHeight(Node<T>* node) {
	node->height = std::max(height(node->left), height(node->right)) + 1;
}

template <class T>
Node<T>*	rightRotate(Node<T>* node) {
	Node<T>* x = node;
	Node<T>* y = node->left;
	x->left = y->right;
	y->right = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}

template <class T>
Node<T>*	leftRotate(Node<T>* node) {
	Node<T>* x = node;
	Node<T>* y = node->right;
	x->right = y->left;
	y->left = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}

template <class T>
Node<T>*	balanceNode(Node<T>* node, Node<T>* new_node) {
	int balance_factor = getBalance(node);
	if (balance_factor > BALANCE_MAX && new_node->value < node->left->value) {
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && new_node->value > node->right->value) {
		return leftRotate(node);
	}
	else if (balance_factor > BALANCE_MAX && new_node->value > node->left->value) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && new_node->value < node->right->value) {
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
	if (new_node->value < node->value) {
		node->left = insertNode(node->left, new_node);
	}
	else if (new_node->value > node->value) {
		node->right = insertNode(node->right, new_node);
	}
	else {
		return node; // do nothing if node is already exist;
	}
	updateHeight(node);
	return balanceNode(node, new_node);
}

//TODO: to delete?
template <class T>
Node<T>*	treeSearch(Node<T>* node, const T& value) {
	if (!node || value == node->value) {
		return node;
	}
	if (value < node->value) {
		return treeSearch(node->left, value);
	}
	return treeSearch(node->right, value);
}

} /* end of namespace AVL */

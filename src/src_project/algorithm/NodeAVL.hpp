#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#define BALANCE_MIN -1
#define BALANCE_MAX 1

namespace AVL {

struct NodeBase {
	NodeBase*	left;
	NodeBase*	right;
	NodeBase*	parent;
	int			height;
	NodeBase(NodeBase* x, NodeBase* y, int h): left(x), right(x), parent(y), height(h) {};
	virtual ~NodeBase() {};
};

template <class T>
struct Node: public NodeBase {
	T			value;
	Node(NodeBase* x, NodeBase* y, const T& src): NodeBase(x, y, 1), value(src) {};
};

bool	isEdge(NodeBase* node);
bool	isSentinel(NodeBase* node);
int	height(NodeBase* node); 
int	getBalance(NodeBase* node);
void	updateHeight(NodeBase* node);
NodeBase* 	minimumNode(NodeBase*  node);
const NodeBase* 	minimumNode(const NodeBase*  node);
NodeBase* 	maximumNode(NodeBase*  node);
const NodeBase* 	maximumNode(const NodeBase*  node);
NodeBase*	rightRotate(NodeBase* x);
NodeBase*	leftRotate(NodeBase* x);
NodeBase*	incrementNode(NodeBase* node);
NodeBase*	decrementNode(NodeBase* node);

template <class T>
NodeBase*	balanceNode(NodeBase* node, NodeBase* new_node) {
	int balance_factor = getBalance(node);
	if (balance_factor > BALANCE_MAX && static_cast< Node<T>* >(new_node)->value < static_cast< Node<T>* >(node->left)->value) { // TODO: to add value_compare
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && static_cast< Node<T>* >(node->right)->value < static_cast< Node<T>* >(new_node)->value) { // TODO: to add value_compare
		return leftRotate(node);
	}
	else if (balance_factor > BALANCE_MAX && static_cast< Node<T>* >(node->left)->value < static_cast< Node<T>* >(new_node)->value ) { // TODO: to add value_compare
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	else if (balance_factor < BALANCE_MIN && static_cast< Node<T>* >(new_node)->value < static_cast< Node<T>* >(node->right)->value) { // TODO: to add value_compare
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	else {
		return node;
	}
}

/* do nothing if node already exists */
template <class T>
NodeBase*	insertNode(NodeBase* node, NodeBase* new_node) {
	if (!node) {
		return new_node;
	}
	if (!new_node) {
		return node;
	}
	if (static_cast< Node<T>* >(new_node)->value < static_cast< Node<T>* >(node)->value) { // TODO: to add value_compare
		node->left = insertNode<T>(node->left, new_node);
		node->left->parent = node; //TODO: to evaluate efficiency: check if node->left->parent == NULL first?
	}
	else if (static_cast< Node<T>* >(node)->value < static_cast< Node<T>* >(new_node)->value) { // TODO: to add value_compare
		node->right = insertNode<T>(node->right, new_node);
		node->right->parent = node;
	}
	else {
		return node; // do nothing if node is already exist;
	}
	updateHeight(node);
	return balanceNode<T>(node, new_node);
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

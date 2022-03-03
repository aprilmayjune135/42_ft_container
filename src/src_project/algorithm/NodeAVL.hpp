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

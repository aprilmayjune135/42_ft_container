#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

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
	~Node() {};
};

bool	isEdge(NodeBase* node);
bool	isSentinel(NodeBase* node);
bool	notLeaf(NodeBase* node);
int	height(NodeBase* node); 
int	getBalance(NodeBase* node);
bool	isLeftHeavy(int balance_factor);
bool	isRightHeavy(int balance_factor);
void	updateHeight(NodeBase* node);
NodeBase* 	minimumNode(NodeBase*  node);
const NodeBase* 	minimumNode(const NodeBase*  node);
NodeBase* 	maximumNode(NodeBase*  node);
const NodeBase* 	maximumNode(const NodeBase*  node);
NodeBase*	rightRotate(NodeBase* x);
NodeBase*	leftRotate(NodeBase* x);
NodeBase*	incrementNode(NodeBase* node);
NodeBase*	decrementNode(NodeBase* node);

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

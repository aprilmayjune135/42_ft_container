#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#define RBT_RED 1
#define RBT_BLACK 0

namespace RBT {

/*
5 rules for RBT
	- Every node is either Black or Red
	- Root ndoe is Black
	- Every leaf node is Black
	- Red node cannot have red parent or children
	- Every path from a node to NULL node has the same number of black nodes
*/

struct NodeBase {
	NodeBase*	left;
	NodeBase*	right;
	NodeBase*	parent;
	int			color;
	NodeBase(NodeBase* x, NodeBase* y, int color): left(x), right(x), parent(y), color(color) {};
	virtual ~NodeBase() {};
};

template <class T>
struct Node: public NodeBase {
	T			value;
	Node(NodeBase* x, NodeBase* y, const T& src): NodeBase(x, y, RBT_RED), value(src) {};
	~Node() {};
};

bool	isEdge(NodeBase* node);
bool	isSentinel(NodeBase* node);
bool	notLeaf(NodeBase* node);
bool	isBlack(NodeBase* node);
bool	isRed(NodeBase* node);
bool	isLeftChild(NodeBase* node);
bool	isRightChild(NodeBase* node);
NodeBase*	getUncle(NodeBase* node);
NodeBase*	getSibling(NodeBase* node);

NodeBase* 	minimumNode(NodeBase*  node);
const NodeBase* 	minimumNode(const NodeBase*  node);
NodeBase* 	maximumNode(NodeBase*  node);
const NodeBase* 	maximumNode(const NodeBase*  node);

NodeBase*	incrementNode(NodeBase* node);
NodeBase*	decrementNode(NodeBase* node);

} /* end of namespace RBT */

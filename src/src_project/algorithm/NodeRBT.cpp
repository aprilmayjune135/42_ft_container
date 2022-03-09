#include "NodeRBT.hpp"
#define BALANCE_MIN -1
#define BALANCE_MAX 1


namespace RBT {

bool	isSentinel(NodeBase* node) {
	return node && node->left == node && node->right == node;
}

bool	isEdge(NodeBase* node) {
	return !node || isSentinel(node);
}

bool	notLeaf(NodeBase* node) {
	return node && (!isEdge(node->left) || !isEdge(node->right));
}

bool	isBlack(NodeBase* node) {
	return isEdge(node) || node->color == RBT_BLACK;
}

bool	isRed(NodeBase* node) {
	return !isEdge(node) && node->color == RBT_RED;
}

/* assume Parent is not NULL or Sentinel */
bool	isLeftChild(NodeBase* node) {
	return node == node->parent->left;
}

/* assume Parent is not NULL or Sentinel */
bool	isRightChild(NodeBase* node) {
	return node == node->parent->right;
}

/* assume Grandparent is not NULL or Sentinel */
NodeBase*	getUncle(NodeBase* node){
	if (isLeftChild(node->parent)) {
		return node->parent->parent->right;
	}
	return node->parent->parent->left;
}

NodeBase* 	minimumNode(NodeBase*  node) {
	while (notLeaf(node) && node->left) {
		node = node->left;
	}
	return node;
}

NodeBase* 	maximumNode(NodeBase*  node) {
	while (notLeaf(node) && !isEdge(node->right)) {
		node = node->right;
	}
	return node;
}

NodeBase*	rightRotate(NodeBase* x) {
	NodeBase* y = x->left;
	y->parent = x->parent;
	x->left = y->right;
	if (!isEdge(x->left)) {
		x->left->parent = x;
	}
	y->right = x;
	x->parent = y;
	return y;
}

NodeBase*	leftRotate(NodeBase* x) {
	NodeBase* y = x->right;
	y->parent = x->parent;
	x->right = y->left;
	if (!isEdge(x->right)) {
		x->right->parent = x;
	}
	y->left = x;
	x->parent = y;
	return y;
}

NodeBase*	incrementNode(NodeBase* node) {
	if (!node) {
		return NULL;
	}
	if (!isEdge(node) && node->right) {
		node = node->right;
		while (!isEdge(node->left)) {
			node = node->left;
		}
		return node;
	}
	else {
		NodeBase* temp = node->parent;
		while (node == temp->right) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

NodeBase*	decrementNode(NodeBase* node) {
	if (!node) {
		return NULL;
	}
	if (!isEdge(node) && node->left) {
		node = node->left;
		while (!isEdge(node->right)) {
			node = node->right;
		}
		return node;
	}
	else {
		NodeBase* temp = node->parent;
		while (node == temp->left) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

} /* end of namespace RBT */

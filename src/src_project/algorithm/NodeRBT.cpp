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

void	flipColor(NodeBase* node) {
	// if node is root and color is black, do not flip color
	if (isEdge(node) || (isSentinel(node->parent) && node->color == RBT_BLACK)) {
		return ;
	}
	node->color = !(node->color);
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

} /* end of namespace RBT */

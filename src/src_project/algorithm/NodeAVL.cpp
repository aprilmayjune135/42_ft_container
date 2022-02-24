#include "NodeAVL.hpp"

namespace AVL {

bool	isSentinel(NodeBase* node) {
	return node->height == 0;
}

int height(NodeBase* node) {
	if (!node) {
		return 0;
	}
	return node->height;
}

int	getBalance(NodeBase* node) {
	if (!node) {
		return 0;
	}
	return height(node->left) - height(node->right);
}

void	updateHeight(NodeBase* node) {
	node->height = std::max(height(node->left), height(node->right)) + 1;
}

NodeBase* 	minimumNode(NodeBase*  node) {
	while (node && node->height > 1) {
		node = node->left;
	}
	return node;
}

const NodeBase* 	minimumNode(const NodeBase*  node) {
	while (node && node->height > 1) {
		node = node->left;
	}
	return node;
}

NodeBase* 	maximumNode(NodeBase*  node) {
	while (node && node->height > 1) {
		node = node->right;
	}
	return node;
}

const NodeBase* 	maximumNode(const NodeBase*  node) {
	while (node && node->height > 1) {
		node = node->right;
	}
	return node;
}

NodeBase*	rightRotate(NodeBase* x) {
	NodeBase* y = x->left;
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

NodeBase*	leftRotate(NodeBase* x) {
	NodeBase* y = x->right;
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

NodeBase*	incrementNode(NodeBase* node) {
	if (!isSentinel(node) && node->right) {
		node = node->right;
		while (node->left) {
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
	if (!isSentinel(node) && node->left) {
		node = node->left;
		while (node->right) {
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


} /* end of namespace AVL */

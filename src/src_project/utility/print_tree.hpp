#pragma once
#include "../algorithm/NodeAVL.hpp"
#include "../algorithm/NodeRBT.hpp"
#include "print_container.hpp"
#include <string>
#include <iostream>

namespace utility {

// TODO: to review
// https://www.techiedelight.com/c-program-print-binary-tree/
struct Trunk {
	Trunk* 		prev;
	std::string	str;
	Trunk(Trunk* prev, std::string str): prev(prev), str(str) {};
};

void	showTrunk(Trunk* p);

template <class T>
void	printNode(AVL::NodeBase* root, Trunk* prev, bool isLeft) {
	if (!root || isSentinel(root)) {
		return ;
	}
	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	printNode<T>(root->right, trunk, true);
	if (!prev) {
		trunk->str = "———";
	}
	else if(isLeft) {
		trunk->str = ".———";
		prev_str = "    |";
	}
	else {
        trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunk(trunk);
	PRINT << " ";
	printPair(static_cast< AVL::Node<T>* >(root)->value);
	// PRINT << static_cast< AVL::Node<T>* >(root)->height;
	if (isSentinel(root->right)) {
		PRINT << '$';
	}
	if (isSentinel(root->parent)) {
		PRINT << '*';
	}
	PRINT << '\n';
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "    |";
	printNode<T>(root->left, trunk, false);
}


template <class T>
void	printNode(RBT::NodeBase* root, Trunk* prev, bool isLeft) {
	if (!root || isSentinel(root)) {
		PRINT << "EMPTY TREE!\n";
		return ;
	}
	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	printNode<T>(root->right, trunk, true);
	if (!prev) {
		trunk->str = "———";
	}
	else if(isLeft) {
		trunk->str = ".———";
		prev_str = "    |";
	}
	else {
        trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunk(trunk);
	PRINT << " ";
	printPair(static_cast< RBT::Node<T>* >(root)->value);
	static_cast< RBT::Node<T>* >(root)->color == RBT_RED ? (PRINT << "[R]") : (PRINT << "[B]");
	if (isSentinel(root->right)) {
		PRINT << '$';
	}
	if (isSentinel(root->parent)) {
		PRINT << '*';
	}
	PRINT << '\n';
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "    |";
	printNode<T>(root->left, trunk, false);
}

} /* end of namespace utility */

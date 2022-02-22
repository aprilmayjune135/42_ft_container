#include <string>
#include <vector>
#include <iostream>

template <class T>
struct Node {
	Node<T>*	left;
	Node<T>*	right;
	T			value;
	Node(const T& value): left(NULL), right(NULL), value(value) {};
};

template <class T>
int	nodeHeight(Node<T>* root) {
	if (!root) {
		return -1;
	}
	if (!root->left && !root->right) {
		return 0;
	}
	return std::max(nodeHeight(root->left), nodeHeight(root->right)) + 1;
}

template <class T>
int	nodeBalance(Node<T>* root) {
	if (!root) {
		return 0;
	}
	return nodeHeight(root->left) - nodeHeight(root->right);
}

template <class T>
Node<T>*	rightRotate(Node<T>* root) {
	Node<T>* x = root;
	Node<T>* y = root->left;
	x->left = y->right;
	y->right = x;
	return y;
}

template <class T>
Node<T>*	leftRotate(Node<T>* root) {
	Node<T>* x = root;
	Node<T>* y = root->right;
	x->right = y->left;
	y->left = x;
	return y;
}

template <class T>
Node<T>*	insertBST(Node<T>* root, Node<T>* new_node) {
	if (!root) {
		root = new_node;
	}
	else {
		Node<T>* temp = root;
		while (temp) {
			if (new_node->value < temp->value) {
				if(!temp->left) {
					temp->left = new_node;
					break ;
				}
				temp = temp->left;
			}
			else {
				if(!temp->right) {
					temp->right = new_node;
					break ;
				}
				temp = temp->right;
			}
		}
	}
	return root;
};

template <class T>
Node<T>*	insertAVL(Node<T>* root, Node<T>* new_node) {
	root = insertBST(root, new_node);
	int balance_factor = nodeBalance(root);
	if (balance_factor > 1 && new_node->value < root->left->value) {
		root = rightRotate(root);
	}
	else if (balance_factor < -1 && new_node->value > root->right->value) {
		root = leftRotate(root);
	}
	else if (balance_factor > 1 && new_node->value > root->left->value) {
		root->left = leftRotate(root->left);
		root = rightRotate(root);
	}
	else if (balance_factor < -1 && new_node->value < root->right->value) {
		root->right = rightRotate(root->right);
		root = leftRotate(root);
	}
	else {}
	return root;
}

// https://www.techiedelight.com/c-program-print-binary-tree/
struct Trunk {
	Trunk* 		prev;
	std::string	str;
	Trunk(Trunk* prev, std::string str): prev(prev), str(str) {};
};

void	showTrunk(Trunk* p) {
	if (p) {
		showTrunk(p->prev);
		std::cout << p->str;
	}
}

template <class T>
void	printNode(Node<T>* node, int level) {
	if (!node) {
		return ;
	}
	printNode(node->left, level + 1);
	std::cout << "[" << level << "]" << node->value << " ";
	printNode(node->right, level + 1);
}

template <class T>
void	printNode(Node<T>* root, Trunk* prev, bool isLeft) {
	if (!root) {
		return ;
	}
	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	printNode(root->right, trunk, true);
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
	std::cout << " " << root->value << '\n';

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "    |";
	printNode(root->left, trunk, false);
}

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

template <class T>
class Tree {
	public:
		Tree(): root(NULL) {};
		~Tree() {};
		Tree(const T& src) {/* TO DO*/};
		template <class InputIterator>
		Tree(InputIterator front, InputIterator back);	
	
		void	init(const T& value) {root = new Node<T>(value);};
		void	insert(const T& value) {
			Node<T>*	new_node = new Node<T>(value);
			root = insertAVL(root, new_node);
		}

		void	print() const {return printNode(root, NULL, false);};
		int		getHeight() const {return nodeHeight(root);};
		int		getBalance() const {return nodeBalance(root);};

	private:
		Node<T>*	root;


};

int main() {
	for (int j = 10; j > 0; --j) {
		Tree<int>	tree;
		for (int i = j; i > 0; --i) {
			tree.insert(i);
		}
		tree.print();
	}
	// std::cout << "Height is: " << tree.getHeight() << '\n';
	// std::cout << "Balance is: " << tree.getBalance() << '\n';
}

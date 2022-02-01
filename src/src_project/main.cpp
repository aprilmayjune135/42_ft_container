#include <iostream>
#include "container/vector.hpp"
#include <vector>


static void	testFT() {
	utility::printTitle("ft_container");
	typedef ft::vector<int>	container_type;
	container_type	lemon(10, 4);
	std::cout << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	for (size_t i = 0; i < lemon.size(); ++i) {
		std::cout << lemon[i] << " ";
	}
	std::cout << '\n';
	for (container_type::iterator it = lemon.begin(); it != lemon.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
	for (container_type::reverse_iterator it = lemon.rbegin(); it != lemon.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
}

static void	testSTD() {
	utility::printTitle("STD_contaienr");
	typedef std::vector<int>	container_type;
	container_type	lemon(10, 4);
	std::cout << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	for (size_t i = 0; i < lemon.size(); ++i) {
		std::cout << lemon[i] << " ";
	}
	std::cout << '\n';
	for (container_type::iterator it = lemon.begin(); it != lemon.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
	for (container_type::reverse_iterator it = lemon.rbegin(); it != lemon.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
}

#ifndef CATCH
int main() {
	testFT();
	testSTD();
}
#endif

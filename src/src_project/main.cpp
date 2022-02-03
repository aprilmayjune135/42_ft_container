#include <iostream>
#include "container/vector.hpp"
#include <vector>


static void	testFT() {
	utility::printTitle("ft_container");
	typedef ft::vector<int>	container_type;
	container_type	lemon(10, 96);
	lemon.assign(5, 2);
	// std::vector<int> src(5, 8);
	// lemon.assign<std::vector<int>::iterator>(src.begin(), src.end());
	container_type src(4, 9);
	lemon.assign<container_type::const_iterator>(src.begin(), src.end());
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
	lemon.assign(5, 2);
	container_type src(5, 8);
	lemon.assign<container_type::iterator>(src.begin(), src.end());
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

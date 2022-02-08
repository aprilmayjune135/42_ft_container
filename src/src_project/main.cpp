#include <iostream>
#include "utility/print_color.hpp"
#include "utility/print_vector.hpp"
#include "container/vector.hpp"
#include "test/test.hpp"
#include <vector>

void	testFT() {
	utility::printTitle("ft_container");
	utility::printYellow(">> basic");
	typedef ft::vector<int>	container_type;
	container_type	lemon(10, 4);
	std::cout << "begin: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	lemon.assign(8, 2);
	std::cout << "assign_fill: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	container_type src = container_type(4, 9);
	std::cout << "operator=: " << src.size() << " | " << src.capacity() << " | " << src.max_size() << '\n';
	lemon.assign<container_type::const_iterator>(src.begin(), src.end());
	std::cout << "assign_range: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
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

	int	array[5] = {1,2,3,4,5};
	int*	first = new int(1);
	int*	second = new int(2);
	int*	third = new int(3);
	container_type	lala(array, array+4);
	std::cout << lala.size() << " | " << lala.capacity() << " | " << lala.max_size() << '\n';
	for (container_type::iterator it = lala.begin(); it != lala.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';


	utility::printYellow(">> push_back");
	container_type	v_push;
	for (int i = 0; i < 10; ++i) {
		v_push.push_back(i * 10);
		std::cout << v_push.size() << "-" << v_push.capacity() << " | " ;
	}
	std::cout << '\n';
	for (container_type::iterator it = v_push.begin(); it != v_push.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> pop_back");
	container_type	v_pop(10, 8);
	for (int i = 0; i < 10; ++i) {
		v_pop.pop_back();
		std::cout << v_pop.size() << "-" << v_pop.capacity() << " | " ;
	}
	std::cout << '\n';

	utility::printYellow(">> insert_fill (1)");
	v_push.insert(v_push.begin() + 3, 7, 44);
	std::cout << v_push.size() << " | " << v_push.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_push.size(); ++i) {
		std::cout << v_push[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_fill (2)");
	v_push.insert(v_push.begin() + 3, 17, 77);
	std::cout << v_push.size() << " | " << v_push.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_push.size(); ++i) {
		std::cout << v_push[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_range (1)");
	container_type	v_insert(1);
	v_insert.insert(v_insert.begin(), lemon.begin(), lemon.end());
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_range (2)");
	v_insert.insert(v_insert.begin(), lemon.begin(), lemon.end());
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_single (1)");
	std::cout << "returned: " << *(v_insert.insert(v_insert.begin(), 101)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';
	std::cout << "returned: " << *(v_insert.insert(v_insert.begin(), 101)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> erase_single");
	std::cout << "returned: " << *(v_insert.erase(v_insert.begin())) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';
	utility::printYellow(">> erase_range");
	std::cout << "returned: " << *(v_insert.erase(v_insert.begin() + 1, v_insert.begin() + 9)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> swap");
	container_type one(1,1);
	container_type two(5,2);
	swap(one, two);
	one.swap(two);
	swap(one, two);
	std::cout << one.size() << " | " << one.capacity() << " | " << '\n';
	for (size_t i = 0; i < one.size(); ++i) {
		std::cout << one[i] << " ";
	}
	std::cout << '\n';
	std::cout << two.size() << " | " << two.capacity() << " | " << '\n';
	for (size_t i = 0; i < two.size(); ++i) {
		std::cout << two[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> operator");
	container_type a(3,2);
	container_type b(a);
	b[2] = 3;
	std::cout << "a {2, 2, 2} | b {2, 2, 3}" << '\n';
	std::cout << "== " << (a == b) << '\n';
	std::cout << "!= " << (a != b) << '\n';
	std::cout << "< " << (a < b) << '\n';
	std::cout << "<= " << (a <= b) << '\n';
	std::cout << "> " << (a > b) << '\n';
	std::cout << ">= " << (a >= b) << '\n';


}

void	testSTD() {
	utility::printTitle("STD_contaienr");
	utility::printYellow(">> basic");
	typedef std::vector<int>	container_type;
	container_type	lemon(10, 4);
	std::cout << "begin: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	lemon.assign(8, 2);
	std::cout << "assign_fill: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
	container_type src = container_type(4, 9);
	std::cout << "operator=: " << src.size() << " | " << src.capacity() << " | " << src.max_size() << '\n';
	lemon.assign<container_type::const_iterator>(src.begin(), src.end());
	std::cout << "assign_range: " << lemon.size() << " | " << lemon.capacity() << " | " << lemon.max_size() << '\n';
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

	int	array[5] = {1,2,3,4,5};
	int*	first = new int(1);
	int*	second = new int(2);
	int*	third = new int(3);
	container_type	lala(array, array+4);
	std::cout << lala.size() << " | " << lala.capacity() << " | " << lala.max_size() << '\n';
	for (container_type::iterator it = lala.begin(); it != lala.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';


	utility::printYellow(">> push_back");
	container_type	v_push;
	for (int i = 0; i < 10; ++i) {
		v_push.push_back(i * 10);
		std::cout << v_push.size() << "-" << v_push.capacity() << " | " ;
	}
	std::cout << '\n';
	for (container_type::iterator it = v_push.begin(); it != v_push.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> pop_back");
	container_type	v_pop(10, 8);
	for (int i = 0; i < 10; ++i) {
		v_pop.pop_back();
		std::cout << v_pop.size() << "-" << v_pop.capacity() << " | " ;
	}
	std::cout << '\n';

	utility::printYellow(">> insert_fill (1)");
	v_push.insert(v_push.begin() + 3, 7, 44);
	std::cout << v_push.size() << " | " << v_push.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_push.size(); ++i) {
		std::cout << v_push[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_fill (2)");
	v_push.insert(v_push.begin() + 3, 17, 77);
	std::cout << v_push.size() << " | " << v_push.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_push.size(); ++i) {
		std::cout << v_push[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_range (1)");
	container_type	v_insert(1);
	v_insert.insert(v_insert.begin(), lemon.begin(), lemon.end());
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_range (2)");
	v_insert.insert(v_insert.begin(), lemon.begin(), lemon.end());
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> insert_single (1)");
	std::cout << "returned: " << *(v_insert.insert(v_insert.begin(), 101)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';
	std::cout << "returned: " << *(v_insert.insert(v_insert.begin(), 101)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> erase_single");
	std::cout << "returned: " << *(v_insert.erase(v_insert.begin())) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';
	utility::printYellow(">> erase_range");
	std::cout << "returned: " << *(v_insert.erase(v_insert.begin() + 1, v_insert.begin() + 9)) << '\n';
	std::cout << v_insert.size() << " | " << v_insert.capacity() << " | " << '\n';
	for (size_t i = 0; i < v_insert.size(); ++i) {
		std::cout << v_insert[i] << " ";
	}
	std::cout << '\n';

	utility::printYellow(">> swap");
	container_type one(1,1);
	container_type two(5,2);
	one.swap(two);
	std::cout << one.size() << " | " << one.capacity() << " | " << '\n';
	for (size_t i = 0; i < one.size(); ++i) {
		std::cout << one[i] << " ";
	}
	std::cout << '\n';
	std::cout << two.size() << " | " << two.capacity() << " | " << '\n';
	for (size_t i = 0; i < two.size(); ++i) {
		std::cout << two[i] << " ";
	}
	std::cout << '\n';


	utility::printYellow(">> operator");
	container_type a(3,2);
	container_type b(a);
	b[2] = 3;
	std::cout << "a {2, 2, 2} | b {2, 2, 3}" << '\n';
	std::cout << "== " << (a == b) << '\n';
	std::cout << "!= " << (a != b) << '\n';
	std::cout << "< " << (a < b) << '\n';
	std::cout << "<= " << (a <= b) << '\n';
	std::cout << "> " << (a > b) << '\n';
	std::cout << ">= " << (a >= b) << '\n';


}

#ifndef CATCH
int main() {
	TestCase	test;
	test.init();

	// testFT();
	// testSTD();
}
#endif

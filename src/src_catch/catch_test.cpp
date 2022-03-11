#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src_project/container/vector.hpp"
#include <iostream>

TEST_CASE("Exception", "vector")
{
	typedef ft::vector<int>	t_vector;
	bool	check;
	t_vector	vector;
	for (int i = 0; i < 10; ++i) {
		vector.push_back(i);
	}
	t_vector	vector_1(vector);

	// at()
	try {
		check = false;
		vector.at(100);
	}
	catch (const std::out_of_range& e) {
		check = true;
	}
	REQUIRE(check);
	REQUIRE(vector == vector_1);

	// resize()
	try {
		check = false;
		vector.resize(vector.max_size()+1);
	}
	catch (const std::length_error& e) {
		check = true;
	}
	REQUIRE(check);
	REQUIRE(vector == vector_1);
	// reserve()
	try {
		check = false;
		vector.reserve(vector.max_size() + 1);
	}
	catch (const std::length_error& e) {
		check = true;
	}
	REQUIRE(check);
	REQUIRE(vector == vector_1);
	// insert()
	try {
		check = false;
		vector.insert(vector.begin(), vector.max_size() + 1, 0);
	}
	catch (const std::length_error& e) {
		check = true;
	}
	REQUIRE(check);
	REQUIRE(vector == vector_1);
	// assign()
	try {
		check = false;
		vector.assign(vector.max_size() + 1, 0);
	}
	catch (const std::length_error& e) {
		check = true;
	}
	REQUIRE(check);
	REQUIRE(vector.empty());
	// constructor()
	try {
		check = false;
		t_vector vector_2(vector.max_size() + 1);
	}
	catch (const std::length_error& e) {
		check = true;
	}
	REQUIRE(check);
}

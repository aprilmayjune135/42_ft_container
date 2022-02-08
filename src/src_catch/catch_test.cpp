#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src_project/container/vector.hpp"

TEST_CASE("vector", "[size]")
{
	ft::vector<int>	v(1,0);
	for (std::size_t i = 1; i < 100; ++i) {
		v.push_back(i);
		REQUIRE(v.size() == i + 1);
		REQUIRE(*v.begin() == 0);
	}
}

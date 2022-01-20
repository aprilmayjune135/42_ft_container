#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src_project/try/try.hpp"

TEST_CASE("just trying", "[lemon]")
{
	REQUIRE( justTrying(5) == 0);
	REQUIRE( justTrying(6) == 1);
}

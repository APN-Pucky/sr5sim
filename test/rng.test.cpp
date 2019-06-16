#include <iostream>
#include "catch.hpp"
#include "rng.h"


TEST_CASE("RNG", "[rng]") {
	init();
	auto h = hits(10);
	std::cout <<" hits " << h  << std::endl;
	auto s = sum(10);
	std::cout <<" sum " << s << std::endl;
}

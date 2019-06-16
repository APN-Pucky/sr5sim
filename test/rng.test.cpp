#include <iostream>
#include "catch.hpp"
#include "rng.h"


TEST_CASE("RNG", "[rng]") {
	init();
	std::cout << roll(10) << std::endl;
}

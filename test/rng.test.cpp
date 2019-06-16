#include <iostream>
#include "catch.hpp"
#include "rng.h"


TEST_CASE("RNG", "[rng]") {
	init();
	std::cout <<"hits " <<  hits(10) << std::endl;
	std::cout <<"sum " << sum(4) << std::endl;
}

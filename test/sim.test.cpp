#include <iostream>
#include "catch.hpp"
#include "sim.h"
using namespace std;

TEST_CASE("Sim","[sim]") {
	Character c1,c2;
	SimData sd;
	simulate(sd,{c1,c2});
	cout << (sd.res==LOSS) << endl;
}
	
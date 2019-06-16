#include <iostream>
#include "catch.hpp"
#include "load.h"
using namespace std;

TEST_CASE("Battle","[battle]") {
	Character p1,p2;
	p1.stats[body] = 4;
	p1.stats[willpower] = 4;
	p1.stats[reaction] = 4;
	p1.stats[intuition] = 4;
	p1.stats[unarmed_combat] = 4;
	p2.stats[body] = 5;
	p2.stats[willpower] = 5;
	p1.stats[reaction] = 5;
	p1.stats[intuition] = 5;
	p2.stats[unarmed_combat] = 5;
	
	CI c1(p1);
	CI c2(p2);
	
	c1.attack_unarmed_combat(c2);
}
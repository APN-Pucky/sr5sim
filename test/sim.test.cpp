#include <iostream>
#include "catch.hpp"
#include "sim.h"
#include "debug.h"
using namespace std;

TEST_CASE("Sim","[sim]") {
	Character c1,c2;
	c1.uuid = 1;
	SimData sd;
	c1.stats[agility] = 5;
	c2.stats[agility] = 5;
	c1.stats[body] = 4;
	c2.stats[body] = 4;
	c1.stats[armor] = 2;
	c2.stats[armor] = 2;
	c1.stats[reaction] = 4;
	c2.stats[reaction] = 5;
	c1.stats[intuition] = 5;
	c2.stats[intuition] = 4;
	c1.stats[unarmed_combat] = 6;
	c2.stats[unarmed_combat] = 6;
	c1.stats[strength] = 3;
	c2.stats[strength] = 3;
	
	SimData whole;
	debug_print = 0;
	while(whole.wins+whole.losses+whole.stalls < 10)
	{
		simulate(sd,{c1,c2});
		whole += sd;
	}
	debug_print = 2;
	cout << endl << "RES: " << 1.*whole.wins/(whole.losses+whole.wins+whole.stalls) << " " << whole.wins << "/" << whole.losses << "/" << whole.stalls << endl;
	
}
	

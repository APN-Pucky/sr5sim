#include <iostream>
#include "catch.hpp"
#include "sim.h"
#include "debug.h"
using namespace std;

TEST_CASE("Sim","[sim]") {
	Character c1,c2;
	SimData sd;
	c1.stats[agility] = 5;
	c2.stats[agility] = 5;
	c1.stats[reaction] = 5;
	c2.stats[reaction] = 5;
	c1.stats[intuition] = 5;
	c2.stats[intuition] = 6;
	c1.stats[unarmed_combat] = 5;
	c2.stats[unarmed_combat] = 5;
	int wins = 0;
	int loss = 0;
	debug_print = 0;
	while(wins < 10000)
	{
		simulate(sd,{c1,c2});
		if(sd.res==WIN)wins++;
		if(sd.res==LOSS)loss++;
	}
	debug_print = 2;
	cout << endl << "RES: " << 1.*wins/loss << " " << wins << " " << loss << endl;
}
	

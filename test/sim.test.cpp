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
	int wins = 0;
	int loss = 0;
	int stall = 0;
	debug_print = 0;
	while(wins+loss+stall < 100)
	{
		simulate(sd,{c1,c2});
		if(sd.res==WIN)wins++;
		if(sd.res==LOSS)loss++;
		if(sd.res==STALL)stall++;
	}
	debug_print = 2;
	cout << endl << "RES: " << 1.*wins/(loss+wins+stall) << " " << wins << "/" << loss << "/" << stall << endl;
}
	

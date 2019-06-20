#include <iostream>
#include "load.h"
#include "debug.h"
#include "rng.h"

using namespace std;

int main(int argc,char** argv)
{
	init();
	debug_print++;
	std::vector<Character> cs;
	Character c;
	load_character(c,"../own/nick.chum5");
	cs.emplace_back(c);
	for(int i = 0; i  < 10;++i) {
		Character c;
		load_character(c,"../own/ganger.chum5");
		cs.emplace_back(c);
	}
	debug_print--;
	SimData sd;
	//c1.uuid = 1;
	/*
	// 7*3=21
	Character c1,c2;
	c1.stats[agility] = 6;
	c1.stats[strength] = 5;
	c1.stats[willpower] = 1;
	c1.stats[body] = 5;
	c1.stats[armor] = 3;
	c1.stats[reaction] = 4;
	c1.stats[intuition] = 4;
	c1.stats[unarmed_combat] = -1;
	
	c2.stats[agility] = 4;
	c2.stats[strength] = 4;
	c2.stats[willpower] = 4;
	c2.stats[body] = 4;
	c2.stats[armor] = 4;
	c2.stats[reaction] = 4;
	c2.stats[intuition] = 4;
	c2.stats[unarmed_combat] = -1;
	*/
	SimData whole;
	whole.data = {0,0,0,0};
	debug_print=2;
	while(whole.wins+whole.losses+whole.stalls < 10000)
	{
		simulate(sd,cs,true);
		whole +=sd;
		debug_print = 0;
	}
	cout << endl << "RES: " << 1.*whole.wins/(whole.losses+whole.wins+whole.stalls) << " " << whole.wins << "/" << whole.losses << "/" << whole.stalls << endl;
	cout << endl << "Data: " << 1.*whole.data[0]/(whole.losses+whole.wins+whole.stalls) << " " << 1.*whole.data[1]/(whole.losses+whole.wins+whole.stalls) << " "<< 1.*whole.data[2]/(whole.losses+whole.wins+whole.stalls) << " "<< 1.*whole.data[3]/(whole.losses+whole.wins+whole.stalls) << " " <<endl;
	
	
	debug_print--;
	debug_print--;
	
	
}

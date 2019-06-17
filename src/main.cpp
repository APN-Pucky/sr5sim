#include <iostream>
#include "load.h"
#include "debug.h"

using namespace std;

int main(int argc,char** argv)
{
	debug_print++;
	Character c1 = load_character("../own/nick.chum5");
	Character c2 = load_character("../own/ogir.chum5");
	debug_print--;
	SimData sd;
	c1.uid = 1;
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
	int wins = 0;
	int loss = 0;
	int stall = 0;
	debug_print = 0;
	while(wins+loss+stall < 100000)
	{
		simulate(sd,{c1,c2});
		if(sd.res==WIN)wins++;
		if(sd.res==LOSS)loss++;
		if(sd.res==STALL)stall++;
		//cout << endl << "RES: " << 1.*wins/(loss+wins+stall) << " " << wins << "/" << loss << "/" << stall << endl;
	}
	cout << endl << "RES: " << 1.*wins/(loss+wins+stall) << " " << wins << "/" << loss << "/" << stall << endl;
	debug_print = 2;
	
	
}

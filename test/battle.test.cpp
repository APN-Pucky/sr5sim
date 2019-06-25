#include <iostream>
#include "catch.hpp"
#include "load.h"
#include "debug.h"

using namespace std;

TEST_CASE("Battle","[battle]") {
	Weapon ucc;
	ucc.useskill = unarmed_combat;
	ucc.damage_skill = strength;

	Character p1,p2;
	p1.stats[body] = 4;
	p1.stats[agility] = 4;
	p1.stats[willpower] = 4;
	p1.stats[reaction] = 4;
	p1.stats[intuition] = 4;
	p1.stats[unarmed_combat] = 14;
	p1.weapons.emplace_back(ucc);

	p2.stats[body] = 5;
	p2.stats[agility] = 5;
	p2.stats[willpower] = 5;
	p2.stats[reaction] = 5;
	p2.stats[intuition] = 5;
	p2.stats[unarmed_combat] = 15;
	p2.weapons.emplace_back(ucc);
	
	cout << "pre battle" << endl;
	int w1 = 0;
	int w2 = 0;
	debug_print =0;
	for(int i =0; i < 1000;++i) {
	CI c1(p1);
	CI c2(p2);
	c1.current_weapon = ucc;
	c2.current_weapon = ucc;
	while(!c1.ko() && !c2.ko()) {	
		c1.attack_weapon(c2); 
		c2.attack_weapon(c1);
	}
	if(!c1.ko()) w1++;
	if(!c2.ko()) w2++;
	}
	debug_print =2;
	cout << w1 << "/" << w2  << "=" << 1.*w1/w2 << endl;



}

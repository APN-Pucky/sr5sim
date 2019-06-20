#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include <string>
#include "sr5.h"
enum Mode {
	SS,SA,BF,FA,
};

class Weapon {
public:
	string name;
	Stat useattr = agility;
	Stat useskill;
	int use = 0; //pool bonus value
	int reach= 0;
	int damage = 0;
	Stat damage_skill = zero;
	int damage_type = physical;
	int ap=0;
	int rc=0;
	int accuracy = 0;
	Limit accuracy_limit = unlimited;
	int bullets = 1;
	Mode mode =SS;	
	bool smartlink =false;
	bool launcher = false;

	string description() const;
};
#endif

#include <string>
#include "sr5.h"
enum Mode {
	SS,SA,BF,FA,
};

class Weapon {
public:
	string name;
	Stat attr = agility;
	Stat useskill;
	int reach;
	int damage = 0;
	int damage_skill = zero;
	int ap;
	int rc;
	int accuracy = 0;
	Mode mode;	
	bool smartlink;
};

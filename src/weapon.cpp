#include <sstream>
#include "weapon.h"
#include "sr5.h"

string Weapon::description() const
{
	stringstream ss;
	ss << name <<  ", POOL=[" << stats_name[useattr] << "+" << stats_name[useskill] << "], DMG=(" << damage << "+" << stats_name[damage_skill] << ")" << ((damage_type==physical)?"P":(damage_type==stun)?"S":"?") << ", AP=" << ap <<  ", AC=" << accuracy <<", RC=" << rc << ", REACH=" << reach;
	return ss.str();
}

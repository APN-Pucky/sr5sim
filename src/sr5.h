#ifndef SR5_H_INCLUDED /*once*/
#define SR5_H_INCLUDED

#include <string>

using namespace std;

enum Stat {
	//zero 
	zero,
	//attributes
  	body,agility,reaction,strength,willpower,logic,intuition,charisma,edge,essence,magic,resonance,depth,
	//var
	armor,physicalcm,
	//groups
	acting,outdoors,close_combat,engineering,stealth,firearms,electronics,influence,cracking, biotech,athletics, 
	//skills
	unarmed_combat, 
	perception,
	automatics,
	//Specs
	visual,
	assault_rifles,


	num_stat,
};

const string stats_name[num_stat] = {
	//zero
	"Zero",
	//attr
	"Body","Agility", "Reaction", "Strength", "Willpower", "Logic", "Intuition", "Charisma", "Edge" ,"Essence", "Mage", "Ressonace", "Depth",
	//var
	"Armor", "PhysicalCM",
	//groups
	"Acting", "Outdoors", "Close Combat", "Engineering" , "Stealth", "Firearms", "Electronics" ,"Influence" , "Cracking" ,"Biotech" , "Athletics",
	//skills
	"Unarmed Combat", 
	"Perception",
	"Automatics",
	//specs
	"Visual",
	"Assault Rifles",
};
const int group[num_stat] = {
	zero,
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//var
	zero,zero,
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//skills
	close_combat,
	zero,
	firearms,
	//specs
	zero,
	firearms,
};

//map spec to skill
const int skill[num_stat] = {
	//zero
	zero,
	//attributes
  	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//var 
	zero,zero
	//groups
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//skills
	zero,
	zero,
	zero,
	//Specs
	perception,
	automatics,
};

inline string stats_abbrev(int i) {
	string r = stats_name[i].substr(0,3);
	//for (auto & c: r) c = toupper(c);
	return r;
}
#endif

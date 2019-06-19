#ifndef SR5_H_INCLUDED /*once*/
#define SR5_H_INCLUDED

#include <string>

using namespace std;

enum Limit {
	unlimited,physical,mental,social,
};

enum Damage {
	stun,phys,custom,
};

enum Stat {
	//zero 
	zero,
	//attributes
  	body,agility,reaction,strength,willpower,logic,intuition,charisma,edge,essence,magic,resonance,depth,
	//var
	armor,physicalcm,initiative_dice,reach,damage_resistance,
	//groups
	acting,outdoors,close_combat,engineering,stealth,firearms,electronics,influence,cracking, biotech,athletics, 
	//skills
	unarmed_combat, blades,
	automatics,longarms,pistols,
	perception,
	//Specs
	cyber_implants, axes, swords,
	assault_rifles,shotguns,semi_automatics,
	visual,


	num_stat,
};

const string stats_name[num_stat] = {
	//zero
	"Zero",
	//attr
	"Body","Agility", "Reaction", "Strength", "Willpower", "Logic", "Intuition", "Charisma", "Edge" ,"Essence", "Mage", "Ressonace", "Depth",
	//var
	"Armor", "PhysicalCM","InitiativeDice","Reach","DamageResistance",
	//groups
	"Acting", "Outdoors", "Close Combat", "Engineering" , "Stealth", "Firearms", "Electronics" ,"Influence" , "Cracking" ,"Biotech" , "Athletics",
	//skills
	"Unarmed Combat", "Blades",
	"Automatics","Longarms","Pistols",
	"Perception",
	//specs
	"Cyber Implants","Axes", "Swords",
	"Assault Rifles","Shotguns","Semi-Automatics",
	"Visual",
};

//map spec to skill
const int skill[num_stat] = {
	//zero
	zero,
	//attributes
  	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//var 
	zero,zero,zero,zero,zero,
	//groups
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//skills
	zero,zero,
	zero,zero,zero,
	zero,
	//Specs
	unarmed_combat,blades, blades,
	automatics,longarms,pistols,
	perception,
};

//map to group
const int group[num_stat] = {
	zero,
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//var
	zero,zero,zero,zero,zero,
	//group
	zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,zero,
	//skills
	close_combat,close_combat,
	firearms,firearms,firearms,
	zero,
	//specs
	close_combat,close_combat, close_combat,
	firearms,firearms,firearms,
	zero,
};


inline string stats_abbrev(int i) {
	string r = stats_name[i].substr(0,3);
	//for (auto & c: r) c = toupper(c);
	return r;
}
#endif

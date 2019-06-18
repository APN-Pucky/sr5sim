#include <string>
using namespace std;

enum Stat {
	//attributes
  	body,agility,reaction,strength,willpower,logic,intuition,charisma,edge,essence,magic,resonance,depth,
	//skills
	armor, unarmed_combat,
	num_stat,
};


enum StatGroup {
	attribute,

	acting,outdoors,close_combat,engineering,stealth,firearms,electronics,influence,cracking, biotech,athletics, 

	none,
	num_statgroup,
};

const int group[num_stat] = {
	attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,attribute,
	none,close_combat,	
};

const string stats_abbrev[num_stat] = {
	"BOD","AGI", "REA","STR","WIL","LOG","INT","CHA","EDG", "ESS", "MAG", "RES","DEP",

	"ARM","UCC"
};

const string stats_name[num_stat] = {
	"Body","Agility", "Reaction", "Strength", "Willpower", "Logic", "Intuition", "Charisma", "Edge" ,"Essence", "Mage", "Ressonace", "Depth",

	"Armor", "Unarmed Combat",
};

const string statgroups_name[num_statgroup] = {
	"",

	"Acting", "Outdoors", "Close Combat", "Engineering" , "Stealth", "Firearms", "Electronics" ,"Influence" , "Cracking" ,"Biotech" , "Athletics",
	"None",
};

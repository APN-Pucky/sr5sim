#include <functional>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;




enum Stat {
	//attributes
  	body,agility,reaction,strength,willpower,logic,intuition,charisma,edge,essence,magic,resonance,depth,
	//skills
	armor, unarmed_combat,weapon,
	num_stat,
};

const string abbrev[num_stat] = {
	"BOD","AGI", "REA","STR","WIL","LOG","INT","CHA","EDG", "ESS", "MAG", "RES","DEP",
	"ARM","UCC","WEP",
};



struct Character
{
  unordered_map<Stat,int> stats;
  unordered_map<string,string> armor;
  string name,alias;
};


class CharacterInstance
{
	const Character reference;
	Character chr;
	unordered_map<Stat,int>* stats;

	public:
		int phys_dmg = 0;
		int stun_dmg = 0;
		int init_dice = 1;
		int uid = 0;
	public:
		CharacterInstance(Character chr) : reference(chr), chr(reference) {stats = &chr.stats;}
		~CharacterInstance(){}
		// var stat:
		int max_phys();
		int max_ko();
		int max_stun();
		int mali();
		// state
		bool ko();
		bool alive();
		// interact
		void resist_armor_body(int d);
		void reduce_health(int d);
		// eval
		int init();
		int eval_net(initializer_list<Stat> s1,CharacterInstance* c, initializer_list<Stat> s2);
		int eval(initializer_list<Stat> s1);
		// 
		string description();
		string id();
};

using CI = CharacterInstance;


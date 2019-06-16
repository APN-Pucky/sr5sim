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
  //unordered_map<string,string> armor;
  string name,alias;
};


class CharacterInstance
{
	const Character reference;

	int init_dice = 1;
	
	public:
		int current_init_roll = 0;
		int phys_dmg = 0;
		int stun_dmg = 0;
		bool has_acted = false;
		int uid = 0;
		//Character chr;
		unordered_map<Stat,int> stats;
		
	public:
		CharacterInstance(Character chr) : reference(chr), stats(chr.stats) {}
		~CharacterInstance(){}
		// var stat:
		int max_phys();
		int max_ko();
		int max_stun();
		int mali();
		int initiative();
		int current_initiative();
		// state
		bool ko();
		bool alive();
		// interact
		void act(vector<CharacterInstance>);
		void attack_unarmed_combat(CharacterInstance& c);
		void resist_armor_body(int d);
		void take_phys(int d);
		void take_stun(int d);
		// eval
		void init();
		int eval_net(initializer_list<Stat> s1,CharacterInstance& c, initializer_list<Stat> s2, bool apply_enemy_mali=true,bool apply_own_mali=true);
		int eval(initializer_list<Stat> s1, bool apply_mali=true);
		
		// cmp by initiative
		friend bool operator >(const CharacterInstance& x, const CharacterInstance& y);
		friend bool operator <(const CharacterInstance& x, const CharacterInstance>& y);
		// 
		string description();
		string id();
};


using CI = CharacterInstance;

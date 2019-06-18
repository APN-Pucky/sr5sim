#include <functional>
#include <vector>
#include <string>
#include <map>
#include <array>
#include "sr5.h"

using namespace std;



struct Character
{
  array<int,num_stat> stats = {-1}; 
  array<int,num_statgroup> statgroups = {0}; 
  //unordered_map<Stat,int> stats;
  //unordered_map<string,string> armor;
  string name,alias;
  int uuid = 0;

  string description();
  string overview();
  string id();
  int stat(int s);
  int uid();
};


class CharacterInstance
{
	
	public:
		Character reference;
		
		int init_dice = 1;
		int current_init_roll = 0;
		int phys_dmg = 0;
		int stun_dmg = 0;
		bool has_acted = false;
		//Character chr;
		array<int,num_stat> stats;
		array<int,num_statgroup> statgroups;
		//unordered_map<Stat,int> stats;
		
	public:
		CharacterInstance(Character& chr) :reference(chr), stats(chr.stats), statgroups(chr.statgroups) {}
		//~CharacterInstance() {}
		CharacterInstance(const CharacterInstance&)  = default;
		//CharacterInstance& operator =(const CharacterInstance&& x);
		
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
		void act(vector<CharacterInstance>& cs);
		void attack_unarmed_combat(CharacterInstance& c);
		void resist_armor_body(int d, int ap=0, bool stun=false);
		void take_phys(int d);
		void take_stun(int d);
		// eval
		void init();
		int eval_net(initializer_list<Stat> s1,CharacterInstance& c, initializer_list<Stat> s2, bool apply_enemy_mali=true,bool apply_own_mali=true);
		int eval(initializer_list<Stat> s1, bool apply_mali=true);
		
		// cmp by initiative
		friend bool operator >( CharacterInstance& x, CharacterInstance& y);
		friend bool operator <( CharacterInstance& x,  CharacterInstance& y);
		//CharacterInstance& operator =(const CharacterInstance&& x);
		// 
		string description();
		string overview();
		string id();
  		int stat(int s);
		int uid();
};

using CI = CharacterInstance;
using CHR = Character;


#include <functional>
#include <vector>
#include <string>
#include <map>
#include <array>
#include "sr5.h"
#include "weapon.h"

using namespace std;



struct Character
{
  array<int,num_stat> stats = {0}; 
  vector<Weapon> weapons;
  //array<int,num_statgroup> statgroups = {0}; 
  //unordered_map<Stat,int> stats;
  //unordered_map<string,string> armor;
  string name,alias;
  int uuid = 0;

  string description() const;
  string overview() const;
  string id() const;
  int stat(int s) const;
  int uid() const;
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
		array<int,num_stat> mod_stats={0};
		//array<int,num_statgroup> statgroups;
		//unordered_map<Stat,int> stats;
		
	public:
		CharacterInstance(Character& chr) :reference(chr) {}
		//~CharacterInstance() {}
		CharacterInstance(const CharacterInstance&)  = default;
		//CharacterInstance& operator =(const CharacterInstance&& x);
		
		// var stat:
		int physical_limit()const;
		int mental_limit()const;
		int social_limit()const;
		int max_phys() const;
		int max_ko() const;
		int max_stun() const;
		int mali() const;
		int initiative() const;
		int current_initiative() const;
		// state
		bool ko() const;
		bool alive() const;
		// interact
		void act(vector<CharacterInstance>& cs);
		void attack_unarmed_combat(CharacterInstance& c);
		void resist_armor_body(int d, int ap=0, bool stun=false);
		void take_phys(int d);
		void take_stun(int d);
		// eval
		void init();
		int eval_net(initializer_list<Stat> s1, int limit1,CharacterInstance& c, initializer_list<Stat> s2,int limit2, bool apply_enemy_mali=true,bool apply_own_mali=true);
		int eval(initializer_list<Stat> s1,int limit, bool apply_mali=true);
		
		// cmp by initiative
		friend bool operator >( CharacterInstance& x, CharacterInstance& y);
		friend bool operator <( CharacterInstance& x,  CharacterInstance& y);
		//CharacterInstance& operator =(const CharacterInstance&& x);
		// 
		string description()const;
		string overview()const;
		string id()const;
  		int stat(int s)const;
		int uid()const ;
};

using CI = CharacterInstance;
using CHR = Character;


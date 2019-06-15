#include <functional>
using namespace std;

struct Character
{
  int body=0,agility=0,reaction=0,strength=0,willpower=0,logic=0,intuiton=0,charisma=0,edge=0,essence=0,magic=0,resonance=0,depth=0;
};


class CharacterInstance
{
	const Character reference;
	Character character;
	public:
		int health = 100;
		int armor = 10;
	public:
		CharacterInstance(Character chr) : reference(chr) {}
		~CharacterInstance(){}
		void resist_damage(int damage,function<int(CharacterInstance*,int)> block);
};

using CI = CharacterInstance;

// damage functions
int resist_armor_body(CI* c, int d);

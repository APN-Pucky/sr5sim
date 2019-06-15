#include <cassert>
#include "character.h"

void CharacterInstance::resist_damage(int damage, function<int(CI *, int)> block) 
{
	assert(damage >=0);
	health -= block(this,damage);
}

void resist_armor_body(CI* c , int d)
{
	return 0;
}


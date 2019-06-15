#include <iostream>
#include "catch.hpp"
#include "character.h"

using namespace std;

TEST_CASE("TestDMG","[dmg]") {
	Character nil;
	cout << nil.body << endl;
	CharacterInstance ci(nil);
	cout << ci.health << endl;
	ci.resist_damage(100,resist_armor_body);
	cout << ci.health << endl;
}


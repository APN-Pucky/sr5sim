#include <iostream>
#include "catch.hpp"
#include "character.h"

using namespace std;

TEST_CASE("TestDMG","[dmg]") {
	Character nil;
	nil.stats[body] = 5;
	nil.stats[armor] = 50;

	cout << nil.stats[body] << endl;
	CharacterInstance ci(nil);
	cout << ci.health << endl;
	ci.resist_armor_body(100);
	cout << ci.health << endl;
}


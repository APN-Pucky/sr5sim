#include <iostream>
#include "catch.hpp"
#include "load.h"
using namespace std;

TEST_CASE("Load chum5 file","[load]") {
  Character nil = load_character("../test/test.chum5");
  cout << nil.alias<< endl;
  cout << "Strength:" << nil.stats[strength]<< endl;
  cout << "Agility:" <<nil.stats[agility]<< endl;
  cout << "Armor:" <<nil.stats[armor]<< endl;
  cout << "Unarmed Combat:" <<nil.stats[unarmed_combat]<< endl;
}

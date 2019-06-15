#include "catch.hpp"
#include "load.h"
#include <iostream>
using namespace std;

TEST_CASE("Load chum5 file","[load]") {
  const Character nil = load_character("../test/test.chum5");
  cout << nil.body<< endl;
  cout << nil.strength<< endl;
  cout << nil.agility<< endl;
}

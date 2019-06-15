#include "catch.hpp"
#include "load.h"
#include <iostream>
using namespace std;

TEST_CASE("Load chum5 file","[load]") {
  character nil;
  load_character(nil,"../test/test.chum5");
  cout << nil.body<< endl;
  cout << nil.strength<< endl;
  cout << nil.agility<< endl;
}

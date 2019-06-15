#include "catch.hpp"
#include "load.h"
#include <iostream>

TEST_CASE("Load chum5 file","[load]") {
  character nil;
  load_character(nil,"../test/test.chum5");
  std::cout << "ok" << std::endl;
}

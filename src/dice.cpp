#include <stdlib.h>
#include "dice.h"

Dice::Dice(int dices) {
  dices = dice;
  for (int i = 0; i < dice; i++) {
    int d = std::rand() % 6;
    if (d >= 4) {
      hits += 1;
    } else if (d == 0) {
      fails += 1;
    }
  }
  glitch = fails > dice / 2;
  critical = glitch && hits == 0;
}

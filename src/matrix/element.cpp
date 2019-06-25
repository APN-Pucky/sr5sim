#include "element.h"

Element::Element(CharacterInstance& user) : owner(user) {}

void Element::mark(Commlink& comm) {
  if (!marks.contains(comm) || marks[comm] <= 2) {
    marks[comm] += 1;
  }
}

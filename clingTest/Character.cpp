#include "Character.h"
#include <boost/format.hpp>

Character::Character(string name, double hp, double armor, double damage):  name(name), hp(hp), hpmax(hp), armor(armor), damage(damage) {}

string Character::str() {
  boost::format fmt = boost::format("%s (%.1f %%)") % name % (100.0 * hp / hpmax);
  return fmt.str();
}

void Character::attack(Character& target) {
  target.takeDamage(damage);
}

void Character::takeDamage(double dmg) {
  hp -= dmg * 100 / armor;
}

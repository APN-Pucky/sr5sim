#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

using namespace std;

class Character {
private:
  double hp, hpmax;
  double armor;
  double damage;
  string name;
public:
  Character(string name = "Person", double hp = 100, double armor = 100, double damage = 10);
  string str();
  void attack(Character target);
  void takeDamage(double dmg);
};

#endif

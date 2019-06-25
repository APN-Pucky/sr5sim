#include "commlink.h"

Commlink::Commlink(int rat, int code) {
  rating = rat;
  commcode = code;
}

void Commlink::check() {
  matrixDMG = std::min(matrixDMG, getMonitor());
}

void Commlink::resistDamage(int damage) {
  Dice roll = Dice(rating + getFirewall());
  takeDamage(damage - roll.hits);
}

void Commlink::takeDamage(int damage) {
  int dmg = std::max(damage, 0);
  matrixDMG -= dmg;
  check();
}

void Commlink::sendMessage(Commlink& comm, std::string& message) {
  comm.receiveMessage(message);
}

void Commlink::receiveMessage(std::string& message) {
  popup.push_back(message);
}

void Commlink::newFile(std::string& message) {
  storage.push_back(File(message));
}

void Commlink::editIcon() {

}

void Commlink::matrixSearch(std::string& searchString) {
  int hits = std::min(owner.stats[computer] + owner.stats[logic], storage.getDataProcessing());
}

void Commlink::changeGrid(Grid& newGrid) {
  grid = newGrid; // TODO comparison
}

int Commlink::getMonitor() {
  return 8 + (rating+1) / 2;
}

int Commlink::getDataProcessing() {
  return rating;
}

int Commlink::getFirewall() {
  return rating;
}

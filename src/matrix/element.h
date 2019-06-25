#include <unordered_map>

class Element {
private:
  std::unordered_map<Commlink, int> marks;
  CharacterInstance owner; //TODO Persona

public:
  Element(CharacterInstance& user);
  void mark(Commlink& comm); // Personas have marks referenced
}

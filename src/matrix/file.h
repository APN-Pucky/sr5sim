#include<string>

class File : public Element {
public:
  File(std::string& message, Commlink& comm, CharacterInstance& person) : Element(person);
  string data;
  int bombrating;
  bool bombdelete;
  int protection;
  Commlink storage;
  void protect();
}

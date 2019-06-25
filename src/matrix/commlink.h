#include<string>
#include<vector>
#include<unordered_map>

enum State {
  nominal, bricked, glitched, broken
};

enum Grid {
  open, local, global
};

class Commlink : public Element {
public:
  int matrixDMG = 0;
  int rating;
  int commcode;
  std::vector<std::string> popup = {};
  std::vector<File> storage = {};
  Grid grid = Grid.open;

  State state = State.nominal;
  Commlink(int rat, int code);
  void check();

  void resistDamage(int damage);
  void takeDamage(int damage);
  void mark(Commlink comm);

  void sendMessage(Commlink& comm, std::string& message);
  void receiveMessage(string message);

  void newFile(std::string& message);
  void editIcon(); //TODO
  void matrixSearch(std::string& searchString);
//  void fullDefence();
  void changeGrid(Grid& newGrid);

  int getMonitor();
  int getDataProcessing();
  int getFirewall();

};

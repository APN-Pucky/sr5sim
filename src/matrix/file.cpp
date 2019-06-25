#include "file.h"

File::File(std::string& message, Commlink& comm, CharacterInstance& person) : data(message) {}

void File::protect() {
  if (!protection) {
    std::min(owner.stats[computer] + owner.stats[logic], storage.getDataProcessing());
  }
}

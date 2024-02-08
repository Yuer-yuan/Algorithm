#include "burrows_wheeler.h"
#include <cstring>
#include <stdexcept>

int main(int argc, char* argv[]) {
  std::string file;
  if (argc == 3) {
    file = std::string(argv[2]);
  } else {
    file = std::string("");
  }
  if (strcmp(argv[1], "-") == 0) {
    BurrowsWheeler::transform(file);
  } else if (strcmp(argv[1], "+") == 0) {
    BurrowsWheeler::inverse_transeform(file);
  } else {
    throw std::runtime_error("usage: ./burrows -/+");
  }
  return 0;
}

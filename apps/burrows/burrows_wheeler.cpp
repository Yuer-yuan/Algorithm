#include <cstring>
#include <stdexcept>
#include "burrows_wheeler.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    throw std::runtime_error("usage: ./burrows -/+");
  }
  if (strcmp(argv[1], "-") == 0) {
    BurrowsWheeler::transform();
  } else if (strcmp(argv[1], "+") == 0) {
    BurrowsWheeler::inverse_transeform();
  } else {
    throw std::runtime_error("usage: ./burrows -/+");
  }
  return 0;
}

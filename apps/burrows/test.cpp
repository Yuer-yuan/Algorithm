#include <cstdint>
#include <vector>
#include "circular_suffix_array.h"

int main() {
  std::string const s{"banana$"};
  std::vector<uint8_t> const str(s.begin(), s.end());
  CircularSuffixArray const csa(str);
  csa.dump(std::cout);
}

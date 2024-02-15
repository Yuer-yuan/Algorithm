#include <unistd.h>
#include <cstdint>
#include <format>
#include <iostream>
#include "IO/bitstream.hpp"

int main() {
  bool const bit1 = alg::in_bitstream.read_bit();
  bool const bit2 = alg::in_bitstream.read_bit();
  uint8_t const ch1 = alg::in_bitstream.read_char();
  uint8_t const ch2 = alg::in_bitstream.read_char();
  uint32_t const it1 = alg::in_bitstream.read_int();
  bool const bit3 = alg::in_bitstream.read_bit();
  bool const bit4 = alg::in_bitstream.read_bit();
  uint64_t const ln1 = alg::in_bitstream.read_long();
  std::cout << std::format(
      "bit\n  1: {}\n  2: {}\n  3: {}\n  4: {}\n"
      "char\n  1: {}\n  2: {}\n"
      "int: {}\n"
      "long: {}\n",
      bit1, bit2, bit3, bit4, ch1, ch2, it1, ln1);
  return 0;
}

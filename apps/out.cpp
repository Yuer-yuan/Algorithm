#include <unistd.h>
#include <cstdint>
#include <iostream>
#include "IO/bitstream.hpp"

int main() {
  alg::out_bitstream.write_bit(0);
  alg::out_bitstream.write_bit(1);
  alg::out_bitstream.write_char(67);
  alg::out_bitstream.write_char(22);
  alg::out_bitstream.write_int(124);
  alg::out_bitstream.write_bit(1);
  alg::out_bitstream.write_bit(0);
  alg::out_bitstream.write_long(333559);
  alg::out_bitstream.flush();
  return 0;
}

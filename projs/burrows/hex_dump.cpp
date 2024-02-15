#include <iomanip>
#include <iostream>

int main() {
  size_t cnt = 0;
  char c;
  while (std::cin.read(&c, sizeof(c))) {
    cnt++;
    std::cout << std::setbase(16) << std::setw(2) << std::setfill('0')
              << (0xff & c) << ' ';
  }
  std::cout << '\n'
            << std::setbase(10) << (size_t)cnt * sizeof(c) << " bytes\n";
  return 0;
}

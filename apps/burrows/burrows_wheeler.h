#ifndef __ALG_APP_BURROWS_BURROWS_WHEELER_H__
#define __ALG_APP_BURROWS_BURROWS_WHEELER_H__

#include <array>
#include <cstdint>
#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "circular_suffix_array.h"

class BurrowsWheeler {
 public:
  static void transform() {
    auto const str = readStr();
    CircularSuffixArray csa(str);
    size_t first;
    size_t const n = csa.length();

    // `first` is where index 0 appear
    for (size_t i = 0; i < n; i++) {
      if (csa.index(i) == 0) {
        first = i;
        break;
      }
    }

    // dump last col of sorted suffixes
    std::cout.write((char*)&first, sizeof(size_t));
    for (size_t i = 0; i < n; i++) {
      std::cout.write((char*)&str[(csa.index(i) + n - 1) % n], sizeof(uint8_t));
    }
    std::cout.flush();
  }

  static void inverse_transeform() {
    size_t first;
    std::cin.read((char*)&first, sizeof(size_t));
    auto const str = readStr();

    auto const n = str.size();
    auto const R = CircularSuffixArray::getR();
    std::vector<size_t> next(n);
    std::vector<uint8_t> f(n);

    // deduce `next` in linear time
    // https://github.com/mingyueanyao/algorithms-princeton-coursera/blob/master/Codes%20of%20Programming%20Assignments/part2/pa5-burrows/CircularSuffixArray.java
    std::array<size_t, R + 1> count;
    count.fill(0);
    for (size_t i = 0; i < n; i++) {
      auto const c = str[i];
      if ((size_t)c >= R) {
        std::string const err_msg = std::format("char range exceed: {}", c);
        throw std::runtime_error(err_msg);
      }
      count[c + 1] += 1;
    }
    for (size_t i = 0; i < R; i++) {
      count[i + 1] += count[i];
    }
    for (size_t i = 0; i < n; i++) {
      auto const c = (uint8_t)str[i];
      auto const j = count[c];
      f[j] = c;
      next[j] = i;
      count[c] += 1;
    }

    // dump orginal text
    for (size_t i = 0; i < n; i++) {
      std::cout.write((char*)&f[first], sizeof(uint8_t));
      first = next[first];
    }

    std::cout.flush();
  }

 private:
  static std::vector<uint8_t> readStr() {
    std::vector<uint8_t> str;
    uint8_t c;
    while (std::cin.read((char*)&c, sizeof(uint8_t))) {
      str.push_back(c);
    }
    return str;
  }
};
#endif  // !__ALG_APP_BURROWS_BURROWS_WHEELER_H__

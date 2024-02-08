#ifndef __ALG_APP_BURROWS_BURROWS_WHEELER_H__
#define __ALG_APP_BURROWS_BURROWS_WHEELER_H__

#include <array>
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "circular_suffix_array.h"

class BurrowsWheeler {
  static constexpr size_t R = 256;

 public:
  // a possible implement way is to use suffix array (SA)
  // with a char (smaller than any of the text)
  // appended to the text and SA sort 
  // ($n^2 log{n}$ in plain sort and linear time in Karkkainen-Sanders)
  static void transform(std::string const& file = "") {
    std::vector<uint8_t> str;
    if (file.size() == 0) {
      uint8_t c;
      while (std::cin.read((char*)&c, sizeof(uint8_t))) {
        str.push_back(c);
      }
    } else {
      std::ifstream f(file, std::ios::in | std::ios::binary);
      f.seekg(0, std::ios::end);
      size_t size = f.tellg();
      str.resize(size);
      f.seekg(0, std::ios::beg);
      f.read((char*)(&str.front()), size);
    }

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

  static void inverse_transeform(std::string const& file = "") {
    size_t first;
    std::vector<uint8_t> str;
    if (file.size() == 0) {
      std::cin.read((char*)&first, sizeof(size_t));
      uint8_t c;
      while (std::cin.read((char*)&c, sizeof(uint8_t))) {
        str.push_back(c);
      }
    } else {
      std::ifstream f(file, std::ios::in | std::ios::binary);
      f.read((char*)&first, sizeof(size_t));
      auto cur_pos = f.tellg();
      f.seekg(0, std::ios::end);
      size_t size = (size_t)f.tellg() - (size_t)cur_pos;
      str.resize(size);
      f.seekg(cur_pos);
      f.read((char*)(&str.front()), size);
    }

    auto const n = str.size();
    std::vector<size_t> next(n);
    std::vector<uint8_t> f(n);

    // deduce `next` in linear time
    // https://github.com/mingyueanyao/algorithms-princeton-coursera/blob/master/Codes%20of%20Programming%20Assignments/part2/pa5-burrows/CircularSuffixArray.java
    std::array<size_t, R + 1> count;
    count.fill(0);
    for (size_t i = 0; i < n; i++) {
      auto const c = str[i];
      count[c + 1] += 1;
    }
    for (size_t i = 0; i < R; i++) {
      count[i + 1] += count[i];
    }
    for (size_t i = 0; i < n; i++) {
      auto const c = str[i];
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
};
#endif  // !__ALG_APP_BURROWS_BURROWS_WHEELER_H__

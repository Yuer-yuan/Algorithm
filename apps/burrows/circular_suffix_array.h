#ifndef __ALG_APP_BURROWS_CIRCULAR_SUFFIX_ARRAY_H__
#define __ALG_APP_BURROWS_CIRCULAR_SUFFIX_ARRAY_H__

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

class CircularSuffixArray {
  std::vector<uint8_t> str_;
  std::vector<size_t> indexes_;  // indexes are stored
  static constexpr size_t R = 256;

 public:
  // be really careful when using `string_view` for `str.c_str()`
  // will truncate at `\0` like c-style string
  // https://stackoverflow.com/questions/16594298/why-stringstreamstr-truncates-string
  CircularSuffixArray(std::vector<uint8_t> const& str) : str_(str) {
    auto const n = str_.size();
    indexes_.reserve(n);
    for (size_t i = 0; i < n; i++) {
      indexes_.push_back(i);
    }
    std::sort(indexes_.begin(), indexes_.end(),
              [&](auto const lhs, auto const rhs) {
                for (size_t i = 0; i < n; i++) {
                  auto const lc = charAt(i, lhs), rc = charAt(i, rhs);
                  if (lc == rc) {
                    continue;
                  }
                  return lc < rc;
                }
                return lhs <= rhs;
              });
  }

  static constexpr size_t getR() { return R; }

  size_t length() const { return indexes_.size(); }

  size_t index(size_t const i) const {
    if (i > indexes_.size()) {
      throw std::runtime_error(
          "Cannot get out-of-range index of sorted suffixes");
    }
    return indexes_[i];
  }

  void dump(std::ostream& os) const {
    os << "CircularSuffixArray of ";
    for (uint8_t c : str_) {
      os << c;
    }
    os << "\ni origin sorted index[i]\n";
    size_t const n = length();
    for (size_t i = 0; i < n; i++) {
      os << i << ' ';
      dump(os, i);
      os << ' ';
      dump(os, indexes_[i]);
      os << ' ' << indexes_[i] << '\n';
    }
  }

  void dump(std::ostream& os, size_t index) const {
    auto const n = length();
    for (size_t i = index; i < n; i++) {
      os << str_[i];
    }
    for (size_t i = 0; i < index; i++) {
      os << str_[i];
    }
  }

 private:
  uint8_t charAt(size_t const i, size_t const index) {
    return str_[(i + index) % str_.size()];
  }
};

#endif  // !__ALG_APP_BURROWS_CIRCULAR_SUFFIX_ARRAY_H__

#ifndef __ALG_SEARCH_COMMON_HPP__
#define __ALG_SEARCH_COMMON_HPP__

#include <cstdint>
#include <functional>
#include <string>

/*
 * hash functions
 */
namespace alg {
template <typename T>
struct Hash {
  constexpr static int hash(T const&) = delete;
};

template <>
struct Hash<int> {
  constexpr static int hash(int const& t) { return t; }
};

template <>
struct Hash<int64_t> {
  constexpr static int hash(int64_t const& t) { return (int)((t >> 32) ^ t); }
};

template <>
struct Hash<float> {
  static int hash(float const& t) {
    int* p = (int*)(&t);
    return *p;
  }
};

template <>
struct Hash<double> {
  static int hash(double const& t) {
    int64_t* p = (int64_t*)(&t);
    return (int)((*p >> 32) ^ *p);
  }
};

template <>
struct Hash<std::string> {
  static int hash(std::string const& t) {
    int r = 17, b = 31;
    int n = (int)t.size();
    for (int i = 0; i < n; i++) {
      r = (r * b) + (int)t[i];
    }
    return r;
  }
};

};  // namespace alg

#endif  // !__ALG_SEARCH_COMMON_HPP__

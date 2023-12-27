#ifndef __ALG_SORT_SHELL_HPP__
#define __ALG_SORT_SHELL_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class Shell {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    size_t n = a.size();
    size_t h = 1;
    while (3 * h + 1 < n) {
      h = 3 * h + 1;
    }
    while (h >= 1) {
      for (size_t i = h; i < n; i++) {
        for (size_t j = i; j >= h && cmp(a[j], a[j - h]); j -= h) {
          std::swap(a[j], a[j - h]);
        }
      }
      h /= 3;
    }
  }
};
};      // namespace alg
#endif  // !__ALG_SORT_SHELL_HPP__

#ifndef __ALG_SORT_SELECTION_HPP__
#define __ALG_SORT_SELECTION_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class Selection {
  using Vector = std::vector<T>;

 public:
  static void sort(std::vector<T>& a) {
    size_t const n = a.size();
    for (size_t i = 0; i < n; i++) {
      size_t min = i;
      for (size_t j = i + 1; j < n; j++) {
        if (cmp(a[j], a[min])) {
          min = j;
        }
      }
      std::swap(a[i], a[min]);
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_SELECTION_HPP__

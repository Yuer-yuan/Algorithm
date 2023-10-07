#ifndef __ALG_SORT_SELECTION_HPP__
#define __ALG_SORT_SELECTION_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Selection {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(std::vector<T>& a, Cmp cmp = Order<T>::less) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
      int min = i;
      for (int j = i + 1; j < n; j++) {
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

#ifndef __ALG_SELECTION_HPP__
#define __ALG_SELECTION_HPP__

#include <vector>

namespace alg {
template <typename T>
class Selection {
 public:
  static void sort(
      std::vector<T>& a,
      bool (*cmp)(T const& t1, T const& t2) = [](T const& t1, T const& t2) {
        return t1 < t2;
      }) {
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

#endif  // !__ALG_SELECTION_HPP__

#ifndef __ALG_SORT_SORT__
#define __ALG_SORT_SORT__

#include <vector>

namespace alg {
template <typename T>
class Shell {
 public:
  static void sort(
      std::vector<T>& a,
      bool (*cmp)(T const& t1, T const& t2) = [](T const& t1, T const& t2) {
        return t1 < t2;
      }) {
    int n = a.size();
    int h = 1;
    while (3 * h + 1 < n) {
      h = 3 * h + 1;
    }
    while (h >= 1) {
      for (int i = h; i < n; i++) {
        for (int j = i; j >= h && cmp(a[j], a[j - h]); j -= h) {
          std::swap(a[j], a[j - h]);
        }
      }
      h /= 3;
    }
  }
};
};      // namespace alg
#endif  // !__ALG_SORT_SORT__

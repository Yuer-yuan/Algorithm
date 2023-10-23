#ifndef __ALG_SORT_COMMON_HPP__
#define __ALG_SORT_COMMON_HPP__

#include <iostream>
#include <vector>

namespace alg {
/* snippet of sort order */
template <typename T>
class Order {
  // default decremental_order
 public:
  // `t1` < `t2`
  static constexpr bool (*less)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 < t2; };

  // `t1` <= `t2`
  static constexpr bool (*less_equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 <= t2; };

  // `t1` == `t2`
  static constexpr bool (*equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 == t2; };

  // `t1` > `t2`
  static constexpr bool (*greater)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 > t2; };

  // `t1` >= `t2`
  static constexpr bool (*greater_equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 >= t2; };

  // if `t1` < `t2`, -1;
  // else if `t1` == `t2`, 0;
  // else 1; (`t1`)
  static constexpr int (*default_three_way_comparator)(T const& t1,
                                                       T const& t2) =
      [](T const& t1, T const& t2) { return t1 < t2 ? -1 : (t1 > t2 ? 1 : 0); };
};

/* reverse elements at [s, e] */
template <typename T>
void reverse(std::vector<T>& v, int const s, int const e) {
  int const n = v.size();
  if (n == 0 || s > e) {
    return;
  }
  auto is_valid = [&](int const p) { return p >= 0 && p < n; };
  if (!is_valid(s) || !is_valid(e)) {
    std::cerr << "reverse error: invalid range\n";
    return;
  }
  int s_ = s - 1, e_ = e + 1;
  while (++s_ != e_ && s_ != --e_) {
    std::swap(v[s_], v[e_]);
  }
}

};  // namespace alg

#endif  // !__ALG_SORT_COMMON_HPP__

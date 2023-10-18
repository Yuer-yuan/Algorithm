#ifndef __ALG_SORT_COMMON_HPP__
#define __ALG_SORT_COMMON_HPP__

namespace alg {
/* snippet of sort order */
template <typename T>
class Order {
  // default decremental_order
 public:
  // `t1` < `t2`
  static bool (*less)(T const& t1, T const& t2) = [](T const& t1, T const& t2) {
    return t1 < t2;
  };

  // `t1` <= `t2`
  static bool (*less_equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 <= t2; };

  // `t1` == `t2`
  static bool (*equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 == t2; };

  // `t1` > `t2`
  static bool (*greater)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 > t2; };

  // `t1` >= `t2`
  static bool (*greater_equal)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 >= t2; };

  // if `t1` < `t2`, -1;
  // else if `t1` == `t2`, 0;
  // else 1; (`t1`)
  static int (*default_three_way_comparator)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 < t2 ? -1 : (t1 > t2 ? 1 : 0); };
};

};  // namespace alg

#endif  // !__ALG_SORT_COMMON_HPP__

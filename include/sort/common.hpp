#ifndef __ALG_SORT_COMMON_HPP__
#define __ALG_SORT_COMMON_HPP__

namespace alg {
/* snippet of sort order */
template <typename T>
class Order {
  // default decremental_order
 public:
  // `t1` < `t2`
  static constexpr bool (*less)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 < t2; };

  // `t1` > `t2`
  static constexpr bool (*greater)(T const& t1, T const& t2) =
      [](T const& t1, T const& t2) { return t1 > t2; };
};

};  // namespace alg

#endif  // !__ALG_SORT_COMMON_HPP__

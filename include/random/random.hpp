#ifndef __ALG_RANDONM_RANDOM__
#define __ALG_RANDONM_RANDOM__

#include <cstdint>
#include <random>
#include <vector>

namespace alg {
template <typename T>
class Random {
 public:
  /*
   * Knuth shuffle
   *
   * In iteration `i`, pick integer `r` in `[0, i]` uniformly at random.
   * Then swap `a[i]` and `a[r]`.
   * Ref:
   * https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
   *
   * Another way is to use `std::shuffle` as follows:
   * `std::shuffle(begin, end, generator)`
   */
  static void shuffle(std::vector<T>& a) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    for (size_t i = 0; i < a.size(); i++) {
      // uniform distribution on closed interval
      // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
      std::uniform_int_distribution<uint64_t> distr(0, i);
      size_t const r = distr(generator);
      std::swap(a[i], a[r]);
    }
  }
};

/*
 * type has to be supported by `uniform_int_distribution`
 * https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
 */
template <typename T = int>
class RandIntGen {
  std::random_device rand_dev_;
  std::mt19937 generator_;
  std::uniform_int_distribution<T> distr_;

 public:
  RandIntGen(T const lo, T const hi)
      : generator_(rand_dev_()), distr_(lo, hi) {}

  T gen() { return distr_(generator_); }

  void rest(T const lo, T const hi) { distr_(lo, hi); }
};
};      // namespace alg
#endif  // !__ALG_RANDONM_RANDOM__

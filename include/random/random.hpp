#ifndef __ALG_RANDONM_RANDOM__
#define __ALG_RANDONM_RANDOM__

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
    int n = a.size();
    for (int i = 0; i < n; i++) {
      // uniform distribution on closed interval
      // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
      std::uniform_int_distribution<int> distr(0, i);
      int r = distr(generator);
      std::swap(a[i], a[r]);
    }
  }
};
};      // namespace alg
#endif  // !__ALG_RANDONM_RANDOM__

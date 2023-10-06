#ifndef __ALG_TIME_TIMER__
#define __ALG_TIME_TIMER__

#include <bits/chrono.h>
#include <chrono>
#include <ratio>

using SystemClock = std::chrono::system_clock;
using HightResolutionClock = std::chrono::high_resolution_clock;

namespace alg {
template <typename Clock>
class Timer {
  std::chrono::time_point<Clock> current;
  std::chrono::duration<double> elapsed;

 public:
  Timer() : current{}, elapsed{std::chrono::duration<double>::zero()} {}
  void start() { current = Clock::now(); }
  void stop() { elapsed += Clock::now() - current; }
  void reset() { elapsed = std::chrono::duration<double>::zero(); }
  double seconds() { return elapsed.count(); }
  double miliseconds() {
    return std::chrono::duration_cast<
               std::chrono::duration<double, std::milli>>(elapsed)
        .count();
  }
};
};  // namespace alg

#endif  // !__ALG_TIME_TIMER__

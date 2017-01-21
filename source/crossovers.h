#ifndef CROSSOVERS_H
#define CROSSOVERS_H

#include <algorithm>
#include <bitset>
#include <random>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * Summary
   *
   * ATTENTION: no thread safe object, it should be created for each
   * thread in your program.
   */
  template <std::size_t N>
  class RandomSplitCrossOver {
  public:
    RandomSplitCrossOver(unsigned seed) :
      _rng(seed),
      _int_dist(0, N-1) {
    }

    Chromosome<N> operator()(const Chromosome<N> &a,
                             const Chromosome<N> &b) const {
      std::bitset<N> dest;
      size_t pos = static_cast<size_t>(_int_dist(_rng));
      for (size_t i=0; i<pos; ++i) {
        dest[i] = a[i];
      }
      for (size_t i=pos; i<a.size(); ++i) {
        dest[i] = b[i];
      }
      return Chromosome<N>(dest);
    }
  private:
    mutable std::mt19937_64 _rng;
    mutable std::uniform_int_distribution<float> _int_dist;
  }; // class RandomSplitCrossOver

  /**
   * Summary
   *
   * ATTENTION: no thread safe object, it should be created for each
   * thread in your program.
   */
  template <std::size_t N>
  class RandomMixCrossOver {
  public:
    RandomMixCrossOver(unsigned seed) :
      _rng(seed),
      _real_dist(0.0f, 1.0f) {
    }

    Chromosome<N> operator()(const Chromosome<N> &a,
                             const Chromosome<N> &b) const {
      std::bitset<N> dest;
      for (size_t i=0; i<a.size(); ++i) {
        if (_real_dist(_rng) < 0.5f) {
          dest[i] = a[i];
        }
        else {
          dest[i] = b[i];
        }
      }
      return Chromosome<N>(dest);
    }
  private:
    mutable std::mt19937_64 _rng;
    std::uniform_real_distribution<float> _real_dist;
  }; // class RandomMixCrossOver

} // namespace GeneticAlgorithms

#endif // CROSSOVERS_H

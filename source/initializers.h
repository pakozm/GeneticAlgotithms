#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <bitset>
#include <limits>
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
  class RandomInitializer {
  public:
    RandomInitializer(unsigned seed, float prob=0.5f) :
      _rng(seed),
      _real_dist(0.0f, 1.0f),
      _prob(prob) {
    }

    Chromosome<N> operator()() const {
      std::bitset<N> dest;
      for (size_t i=0; i<N; ++i) {
        dest[i] = (_real_dist(_rng) < _prob);
      }
      return Chromosome<N>(dest);
    }

  private:
    mutable std::mt19937_64 _rng;
    mutable std::uniform_real_distribution<float> _real_dist;
    const float _prob;
  }; // class RandomMutate

} // namespace GeneticAlgorithms

#endif // INITIALIZERS_H

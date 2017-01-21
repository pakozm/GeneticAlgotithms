#ifndef TRANSFORMS_H
#define TRANSFORMS_H

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
  template<std::size_t N>
  class RandomMutate {
  public:
    RandomMutate(unsigned seed, float prob) :
      _rng(seed),
      _real_dist(0.0f, 1.0f),
      _prob(prob) {
    }

    Chromosome<N> operator()(const Chromosome<N> &source) const {
      std::bitset<N> dest;
      for (size_t i=0; i<source.size(); ++i) {
        if (_real_dist(_rng) < _prob) {
          dest[i] = !source[i];
        }
        else {
          dest[i] = source[i];
        }
      }
      return Chromosome<N>(dest);
    }
  private:
    mutable std::mt19937_64 _rng;
    mutable std::uniform_real_distribution<float> _real_dist;
    float _prob;
  }; // class RandomMutate
  
} // namespace GeneticAlgorithms
#endif // TRANSFORMS_H

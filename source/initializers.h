/*
 * This file is part of GeneticAlgorithms toolkit
 *
 * Copyright 2017, Francisco Zamora-Martinez
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <bitset>
#include <limits>
#include <random>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * This class generates Chromosomes<N> with random gens
   *
   * The functor uses the given probability to decide if a gen should
   * be 0 or 1, following a Bernoulli distribution with parameter
   * p=prob.
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
        // sample from the distribution and decide if 0 or 1
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

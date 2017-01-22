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
#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <bitset>
#include <random>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * This class functor applies random mutations to each gene
   *
   * The mutation probability is used as parameter of a Bernoulli
   * distribution, so when the distribution sample is 0 the gene is
   * left with its original value, and when it is 1, its value is
   * flipped.
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
        // sample from the distribution and decide
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

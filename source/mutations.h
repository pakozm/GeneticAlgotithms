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
#include <unordered_set>

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

    /**
     * Functor which applies random mutations to a given Chromosome
     *
     * The functor follows two code paths:
     *
     * - When the probability of mutation is very high, we assume it
     *   is better to ask every bit if it should be or not mutated.
     *
     * - Otherwise, we assume it is better to draw the number of
     *   mutated bits from a binomial distribution, and proceed
     *   sampling as many bits as necessary from a uniform
     *   distribution.
     */
    Chromosome<N> operator()(const Chromosome<N> &source) const {
      std::bitset<N> dest(source.gens());
      
      if (_prob > 0.2f) {
        // high mutation probability, traverse all bits
        for (size_t i=0; i<source.size(); ++i) {
          if (_real_dist(_rng) < _prob) dest.flip(i);
        }
      }
      else { // _prob <= 0.2f
        // low mutation probability, draw from a binomial
        
        // This set avoids possible repeated mutation candidates
        std::unordered_set<size_t> positions;
        // Sample the number of bits to mutate from this distribution
        std::binomial_distribution<size_t> bdist(source.size(), _prob);
        size_t n_gens_to_mutate = bdist(_rng);
        if (n_gens_to_mutate > 0uL) {
          // Sample which bit should be mutated from next distribution
          std::uniform_int_distribution<size_t> dist(0uL, source.size() - 1);
          size_t n_mutations = 0uL;
          while(n_mutations < n_gens_to_mutate) {
            size_t pos = dist(_rng);
            if (positions.find(pos) == positions.end()) {
              dest.flip(pos);
              positions.insert(pos);
              ++n_mutations;
            }
          }
        }
      }
      return Chromosome<N>(std::move(dest));
    }

  private:
    mutable std::mt19937_64 _rng;
    mutable std::uniform_real_distribution<float> _real_dist;
    float _prob;
  }; // class RandomMutate
  
} // namespace GeneticAlgorithms
#endif // TRANSFORMS_H

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
#ifndef CROSSOVERS_H
#define CROSSOVERS_H

#include <algorithm>
#include <bitset>
#include <random>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * A cross over class based on random position-based split
   *
   * The functor implemented here splits the chromosomes by sampling a
   * random integer, and producing a child which mixes together one
   * piece of one parent and the other from the other parent.
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
      // sample a random integer
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
    mutable std::uniform_int_distribution<size_t> _int_dist;
  }; // class RandomSplitCrossOver


  /**
   * A cross over class based on random mixing of gens
   *
   * The functor implemented here mixes each gene based on a
   * random decision, so each gene has 0.5 probability to come
   * from any of both parents.
   *
   * ATTENTION: no thread safe object, it should be created for each
   * thread in your program.
   */
  template <std::size_t N>
  class RandomMixCrossOver {
  public:
    RandomMixCrossOver(unsigned seed) :
      _rng(seed),
      _int_dist(0u, 1u) {
    }

    Chromosome<N> operator()(const Chromosome<N> &a,
                             const Chromosome<N> &b) const {
      std::bitset<N> dest;
      for (size_t i=0; i<a.size(); ++i) {
        // flip a coin to decide which parent gene copy is at i position
        if (_int_dist(_rng) == 0u) {
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
    mutable std::uniform_int_distribution<size_t> _int_dist;
  }; // class RandomMixCrossOver

} // namespace GeneticAlgorithms

#endif // CROSSOVERS_H

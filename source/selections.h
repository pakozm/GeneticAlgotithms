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
#ifndef SELECTIONS_H
#define SELECTIONS_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * A class which selects population subjects based on their rank
   *
   * A multinomial distribution is build by normalizing subjects
   * rank, and this distribution is sampled for couple selection.
   *
   * ATTENTION: this class is not thread safe, if you need to use it
   * on different threads, be sure each thread receives a different
   * instance.
   */
  template<std::size_t N, typename T=float>
  class RankDistSelection {
  public:

    /// Initializes the algorithm by receiving a random seed
    RankDistSelection(unsigned seed) :
      _rng(seed) {
    }

    /// This functor receives a population and returns selected couples
    std::vector<typename Chromosome<N>::Couple>
    operator()(const std::vector<std::pair<Chromosome<N>, T> > pop,
               size_t result_size=0uL) const {
      std::vector<float> ranks(pop.size());
      // extract all ranks from pop vector
      std::transform(pop.begin(), pop.end(), ranks.begin(),
                     [](std::pair<Chromosome<N>, T> x){ return x.second; });
      // the minimum would be used to check if all ranks are positive
      float min = *std::min_element(ranks.begin(), ranks.end());
      if (min < 0.0f) {
        // if non positive ranks, translate them using -min
	std::transform(ranks.begin(), ranks.end(), ranks.begin(),
		       [min](float x){ return x - min; });
      }

      // the multinomial distribution is computed here
      std::discrete_distribution<int> distribution(ranks.begin(), ranks.end());

      if (result_size == 0uL) result_size = pop.size();

      // generate a vector of couples by sampling from distribution
      std::vector<typename Chromosome<N>::Couple> result(result_size);
      for (size_t i=0; i<result_size; ++i) {
        size_t x_pos = distribution(_rng);
        size_t y_pos = distribution(_rng);
        result[i] = std::make_pair(pop[x_pos].first,
                                   pop[y_pos].first);
      }

      return result;
    }
  private:
    mutable std::mt19937_64 _rng;
  };

} // namespace GeneticAlgorithms

#endif // SELECTIONS_H

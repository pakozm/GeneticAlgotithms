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
#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

#include "chromosome.h"

namespace GeneticAlgorithms {

  /**
   * A class representing a population of Chromosome<N>
   *
   * This class is responsible of the association of Chromosome<N>
   * with their rank and of the selection of couples. Both operations
   * are delegated on two functors.
   */
  template<std::size_t N, typename RankFunctor,
           typename T = float>
  class Population {
  public:
    /// a Hypothesis is the combination of gens and their rank
    typedef std::pair<Chromosome<N>, T> Hypothesis;
    
    Population(const RankFunctor &rank_func) :
      _rank_func(rank_func),
      _top(Chromosome<N>(), std::numeric_limits<T>::min()) {
    }

    size_t size() const {
      return _queue.size();
    }

    /// push and rank the given Chromosome<N>
    void push(const Chromosome<N> &x) {
      _queue.push_back(Hypothesis(x, _rank_func(x)));
      if (_top.second < _queue.back().second) _top = _queue.back();
    }

    /// returns the best Hypothesis in the population set
    const Hypothesis &top() const {
      return _top;
    }

    /**
     * Initializes by using the given functor
     *
     * All new Chromosome<N> are push_back into the population without
     * clearing the vector.
     */
    template<typename InitializerFunctor>
    void init(const InitializerFunctor init_func,
              const size_t size) {
      for (size_t i=0; i<size; ++i) {
        push(init_func());
        // std::cout << "    " << x.rank() << " " << x.gens() << std::endl;
      }
      // std::cout << "\n" << std::endl;
    }

    /**
     * Given a selection functor, returns the selection of couples
     *
     * @note It is expected that SelectionFunctor produces a result
     * with the given size.
     */
    template<typename SelectionFunctor>
    std::vector<typename Chromosome<N>::Couple >
    select(const SelectionFunctor &select_func, size_t result_size=0uL) {
      if (result_size == 0uL) result_size = _queue.size();
      return select_func(_queue, result_size);
    }

    /// Clears the vector
    void reset() {
      _queue.clear();
      _top = Hypothesis(Chromosome<N>(), std::numeric_limits<T>::min());
    }

  private:
    RankFunctor _rank_func;
    /// The population set is stored here
    std::vector<Hypothesis> _queue;
    /// The best hypothesis in the set
    Hypothesis _top;
  }; // class Population

} // GeneticAlgorithms

#endif // POPULATION_H

#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

#include "chromosome.h"

namespace GeneticAlgorithms {

  template<std::size_t N, typename RankFunctor,
           typename T = float>
  class Population {
  public:

    typedef std::pair<Chromosome<N>, T> Hypothesis;
    
    Population(const RankFunctor &rank_func) :
      _rank_func(rank_func),
      _top(Chromosome<N>(), std::numeric_limits<T>::min()) {
    }

    void push(const Chromosome<N> &x) {
      _queue.push_back(Hypothesis(x, _rank_func(x)));
      if (_top.second < _queue.back().second) _top = _queue.back();
    }

    const Hypothesis &top() const {
      return _top;
    }

    template<typename InitializerFunctor>
    void init(const InitializerFunctor init_func,
              const size_t size) {
      for (size_t i=0; i<size; ++i) {
        push(init_func());
        // std::cout << "    " << x.rank() << " " << x.gens() << std::endl;
      }
      // std::cout << "\n" << std::endl;
    }

    template<typename SelectionFunctor>
    std::vector<typename Chromosome<N>::Couple >
    select(const SelectionFunctor &select_func,
           const size_t size) {
      return select_func(_queue, size);
    }

    void reset() {
      _queue.clear();
      _top = Hypothesis(Chromosome<N>(), std::numeric_limits<T>::min());
    }

  private:
    RankFunctor _rank_func;
    std::vector<Hypothesis> _queue;
    Hypothesis _top;
  }; // class Population

} // GeneticAlgorithms

#endif // POPULATION_H

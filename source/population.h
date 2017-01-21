#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <queue>
#include <vector>

#include "chromosome.h"

namespace GeneticAlgorithms {

  template<std::size_t N, typename RankFunctor>
  class Population {
  public:
    Population(const RankFunctor &rank_func) :
      _rank_func(rank_func) {
    }

    void push(Chromosome<N> &x) {
      x.setRank(_rank_func);
      _queue.push(x);
    }

    Chromosome<N> top() const {
      return _queue.top();
    }

    template<typename InitializerFunctor>
    void init(const InitializerFunctor init_func,
              const size_t size) {
      for (size_t i=0; i<size; ++i) {
        Chromosome<N> x = init_func();
        x.setRank(_rank_func);
        _queue.push(x);
        // std::cout << "    " << x.rank() << " " << x.gens() << std::endl;
      }
      // std::cout << "\n" << std::endl;
    }

    template<typename SelectionFunctor>
    std::vector<typename Chromosome<N>::Couple >
    select(const SelectionFunctor &select_func,
           const size_t size) {
      std::vector<Chromosome<N> > pop;
      while(!_queue.empty()) {
        pop.push_back(_queue.top());
        _queue.pop();
        // std::cout << "    " << pop.back().rank() << " " << pop.back().gens() << std::endl;
      }
      return select_func(pop, size);
    }

  private:
    RankFunctor _rank_func;
    std::priority_queue<Chromosome<N> > _queue;
  }; // class Population

} // GeneticAlgorithms

#endif // POPULATION_H

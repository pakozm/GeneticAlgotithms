#ifndef GENETIC_SOLVER_H
#define GENETIC_SOLVER_H

#include <iostream>

#include "chromosome.h"
#include "population.h"

namespace GeneticAlgorithms {
  /**
   * ATTENTION this function maximizes by default, change RankFunctor
   * sign for minimization.
   */
  template<std::size_t N,
           typename InitializerFunctor,
           typename SelectionFunctor,
           typename CrossOverFunctor,
           typename MutationFunctor,
           typename RankFunctor,
           typename T=float>
  Chromosome<N> solve(const size_t num_iterations,
                      const size_t population_size,
                      const InitializerFunctor &init_func,
                      const SelectionFunctor &select_func,
                      const CrossOverFunctor &cross_over_func,
                      const MutationFunctor &mutate_func,
                      const RankFunctor &rank_func,
                      int verbosity=0) {
    Population<N, RankFunctor, T> current(rank_func);
    Population<N, RankFunctor, T> next(rank_func);

    current.init(init_func, population_size);

    typename Population<N, RankFunctor, T>::Hypothesis best = current.top();

    for (size_t i=0; i<num_iterations; ++i) {
      for (auto couple : current.select(select_func,
                                        population_size)) {
        next.push(mutate_func(cross_over_func(couple.first, couple.second)));
      }
      std::swap(current, next);
      next.reset();
      if (best.second < current.top().second) {
        best = current.top();
      }
      if (verbosity > 0) {
        std::cout << i << ": " << best.second << " :: "
                  << current.top().second << " "
                  << current.top().first.gens()
                  << std::endl;
      }
    }

    return best.first;
  }
} // namespace GeneticAlgorithms

#endif // GENETIC_SOLVER_H

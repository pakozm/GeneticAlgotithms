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
           typename RankFunctor>
  Chromosome<N> solve(const size_t num_iterations,
                      const size_t population_size,
                      const InitializerFunctor &init_func,
                      const SelectionFunctor &select_func,
                      const CrossOverFunctor &cross_over_func,
                      const MutationFunctor &mutate_func,
                      const RankFunctor &rank_func,
                      int verbosity=0) {
    Population<N, RankFunctor> current(rank_func);
    Population<N, RankFunctor> next(rank_func);
    Population<N, RankFunctor> work(rank_func);

    current.init(init_func, population_size);

    Chromosome<N> best = current.top();

    for (size_t i=0; i<num_iterations; ++i) {
      for (auto couple : current.select(select_func,
                                        population_size)) {
        Chromosome<N> child = cross_over_func(couple.first,
                                              couple.second);
        Chromosome<N> mutated = mutate_func(child);
        next.push(mutated);
      }
      std::swap(current, next);
      if (best < current.top()) {
        best = current.top();
      }
      if (verbosity > 0) {
        std::cout << i << ": " << best.rank() << " :: "
                  << current.top().rank() << " " << current.top().gens()
                  << std::endl;
      }
    }

    return best;
  }
} // namespace GeneticAlgorithms

#endif // GENETIC_SOLVER_H

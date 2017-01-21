#ifndef SELECTIONS_H
#define SELECTIONS_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

#include "chromosome.h"

namespace GeneticAlgorithms {

  template<std::size_t N>
  class RankDistSelection {
  public:
    RankDistSelection(unsigned seed) :
      _rng(seed) {
    }

    std::vector<typename Chromosome<N>::Couple>
    operator()(const std::vector<Chromosome<N> > pop,
               const size_t result_size) const {
      std::vector<float> ranks(result_size);
      std::transform(pop.begin(), pop.end(), ranks.begin(),
                     [](Chromosome<N> x){ return x.rank(); });
      float min = *std::min_element(ranks.begin(), ranks.end());
      if (min < 0.0f) {
	std::transform(ranks.begin(), ranks.end(), ranks.begin(),
		       [min](float x){ return x - min; });
      }

      std::discrete_distribution<int> distribution(ranks.begin(), ranks.end());

      std::vector<typename Chromosome<N>::Couple> result(result_size);
      for (size_t i=0; i<result_size; ++i) {
        size_t x_pos = distribution(_rng);
        size_t y_pos = distribution(_rng);
        result[i] = std::make_pair(pop[x_pos], pop[y_pos]);
      }

      return result;
    }
  private:
    mutable std::mt19937_64 _rng;
  };

} // namespace GeneticAlgorithms

#endif // SELECTIONS_H

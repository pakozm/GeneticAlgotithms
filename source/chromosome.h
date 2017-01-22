#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <bitset>
#include <cstdint>
#include <cmath>
#include <numeric>

namespace GeneticAlgorithms {
  
  /**
   * A class which represents a complete chromosome for genetic algorithms
   *
   * A Chromosome is represented by its gens combination (a bits
   * set). Indeed, it is a wrapper over a std::bitset in order to make
   * it inmutable.
   */
  template<std::size_t N>
  class Chromosome {
  public:
    typedef std::pair<Chromosome<N>, Chromosome<N> > Couple;
    
    Chromosome(const std::bitset<N> &gens) :
      _gens(gens) {
    }

    Chromosome() {
    }
    
    bool operator[](const size_t i) const {
      return _gens[i];
    }

    size_t size() const {
      return _gens.size();
    }

    const std::bitset<N> &gens() const {
      return _gens;
    }

  private:
    std::bitset<N> _gens;
  }; // class Chromosome

} // namespace GeneticAlgorithms

#endif // CHROMOSOME_H

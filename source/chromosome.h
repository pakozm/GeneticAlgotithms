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
   * A Chromosome is represented by a rank (given by a particular
   * objective function) and its gens combination (a bits vector).
   */
  template<std::size_t N>
  class Chromosome {
  public:
    typedef std::pair<Chromosome<N>, Chromosome<N> > Couple;
    
    Chromosome(const std::bitset<N> &gens,
               float rank=-std::numeric_limits<float>::infinity()) :
      _gens(gens), _rank(rank) {
    }

    Chromosome() : _rank(0.0f) {
    }
    
    bool operator[](const size_t i) const {
      return _gens[i];
    }

    size_t size() const {
      return _gens.size();
    }
  
    const float &rank() const {
      return _rank;
    }

    bool operator<(const Chromosome &other) const {
      return _rank < other._rank;
    }

    bool operator==(const Chromosome &other) const {
      return _rank == other._rank;
    }

    const std::bitset<N> &gens() const {
      return _gens;
    }

  private:
    std::bitset<N> _gens;
    float _rank;
  }; // class Chromosome

} // namespace GeneticAlgorithms

#endif // CHROMOSOME_H

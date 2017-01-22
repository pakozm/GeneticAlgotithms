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
   *
   * A set of utilities is available at `translators.h` which allow
   * the programmer to decode Chromosomes<N> into a different C++
   * types.
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

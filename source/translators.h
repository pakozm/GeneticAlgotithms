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
#ifndef TRANSLATORS_H
#define TRANSLATORS_H

#include <boost/dynamic_bitset.hpp>
#include <iostream>

#include "chromosome.h"

namespace GeneticAlgorithms {
  
  /**
   * This decoder allow to convert Chromosome gens into C++ types
   *
   * C++ types are represented on a fixed number of bits of the
   * gens. Each time a type is decoded, a position pointer is move
   * forward, allowing to decode the next required bits.
   * 
   * ATTENTION: no thread safe object, it should be created for each
   * thread in your program.
   *
   * @note This class doesn't check if the position counter is valid,
   * be careful, invalid positions can lead into memory problems.
   *
   * @code
   * // my_chromosome has 12 bits:
   * //    - 5 bits are a uint32_t
   * //    - 5 bits are a float number in range [0,1]
   * //    - 2 bits are boolean flags
   * decoder = Decoder(my_chromosme);
   * uint32_t x = decoder.decodeUInt32(5); 
   * float y = decoder.decodeFloat(5, 0.0f, 1.0f);
   * bool z1 = decoder.decodeBool();
   * bool z2 =  decoder.decodeBool();
   * @endcode
   */
  class Decoder {
  public:
    Decoder(const Chromosome &chromosome) :
      _gens(chromosome.gens()), _pos(0u) {
    }

    bool decodeBool() {
      return _gens[_pos++];
    }

    uint64_t decodeUInt64(const size_t n) {
      uint64_t x = 0u;
      size_t i = _pos, j = _pos + n - 1;
      for (size_t k=j+1u; k>i; --k) {
        x = (x<<1uL) | static_cast<uint64_t>(_gens[k-1]);
      }
      _pos += n;
      return x;
    }
    
    uint32_t decodeUInt32(const size_t n) {
      uint32_t x = 0u;
      size_t i = _pos, j = _pos + n - 1;
      for (size_t k=j+1u; k>i; --k) {
        x = (x<<1uL) | static_cast<uint32_t>(_gens[k-1]);
      }
      _pos += n;
      return x;
    }

    double decodeDouble(const size_t n,
                        const double min=0.0f,
                        const double max=1.0f) {
      uint64_t x_uint = decodeUInt64(n);
      // assert(min < max);
      double length = max - min;
      double x_double = static_cast<double>
        (double(x_uint)/double((1uL<<n) - 1uL)*length + min);
      return x_double;
    }

    float decodeFloat(const size_t n,
                      const float min=0.0f,
                      const float max=1.0f) {
      uint64_t x_uint = decodeUInt64(n);
      // assert(min < max);
      float length = max - min;
      float x_float = static_cast<float>
        (double(x_uint)/double((1uL<<n) - 1uL)*length + min);
      return x_float;
    }

  private:
    bitset _gens;
    uint32_t _pos;
  }; // class Decoder

  // template <typename N>
  // class EncoderBuilder {
  // public:
  //   class Encoder {
  //     friend class EncoderBuilder;
  //   private:
  //     Encoder(EncoderBuilder *builder);
  //   };
    
  //   void code_uint32(uint32_t val, const size_t i=0u, const size_t j=N-1) {
  //     for (size_t k=j+1; k>i; --k) {
  //       _gens[k-1] = val & 1u;
  //       val >>= 1;
  //     }
  //   }

  //   void code_float(float val, float min, float max,
  //                   const size_t i=0, const size_t j=N-1) {
  //     float length = max - min;
  //     uint32_t x_uint = static_cast<uint32_t>(roundf((val - min) / length));
  //     code_uint32(x_uint, i, j);
  //   }

  // private:
  //   enum types_t {
  //     UINT32,
  //     FLOAT,
  //   };
  //   struct data_desc_t {
  //     types_t type;
  //     size_t num_bits;
  //     float min, max;
  //   };
  //   vector<data_desc_t> description;

    
  //   uint32_t decode_uint32(const size_t i=0,
  //                          const size_t j=N-1) const {
  //     uint32_t x = 0u;
  //     for (size_t k=j+1; k>i; --k) {
  //       x = (x<<1) | static_cast<uint32_t>(_gens[k-1]);
  //     }
  //     return x;
  //   }

  //   float decode_float(float min,
  //                      float max,
  //                      const size_t i=0,
  //                      const size_t j=N-1) const {
  //     uint32_t x_uint = decode_uint32(i, j);
  //     // assert(min < max);
  //     float length = max - min;
  //     return static_cast<float>(static_cast<double>(x_uint)*length + min);
  //   }

} // namespace GeneticAlgorithms

#endif // TRANSLATORS_H

#ifndef TRANSLATORS_H
#define TRANSLATORS_H

#include <bitset>
#include <iostream>

#include "chromosome.h"

namespace GeneticAlgorithms {
  
  /**
   * Summary
   *
   * ATTENTION: no thread safe object, it should be created for each
   * thread in your program.
   */
  template <std::size_t N>
  class Decoder {
  public:
    Decoder(const Chromosome<N> &chromosome) :
      _gens(chromosome.gens()), _pos(0u) {
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

    float decodeFloat(const size_t n,
                      const float min,
                      const float max) {
      uint64_t x_uint = decodeUInt64(n);
      // assert(min < max);
      float length = max - min;
      float x_float = static_cast<float>
        (double(x_uint)/double((1uL<<n) - 1uL)*length + min);
      return x_float;
    }

  private:
    std::bitset<N> _gens;
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

GeneticAlgorithms
=================

This toolkit allow to implement genetic algorithms in a simple way by
using C++ templates and algorithms, so each genetic operator should be
known at compilation time. In order to allow dynamic number of bits in
chromosomes, this implementation relies on `boost::dynamic_bitset`. It
is possible to improve the efficiency a 30% by using `std::bitset` and
compilation time number of bits.

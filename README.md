GeneticAlgorithms
=================

This toolkit allow to implement genetic algorithms in a simple way by
using C++ templates and algorithms. Because that, it relies on
compilation time knowledge about the number of bits necessary to
represent the hypothesis. If your problem requires a dynamic number of
bits probably you should use a different library (or a JIT compiler to
produce the desired code, but this can be hard and slow).

Regarding performance metrics, a straightforward reimplementation of
this library, using dynamic containers (`std::vector<bool>`), is two
times slower.

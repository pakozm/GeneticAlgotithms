#include <iostream>
#include <random>

#include "chromosome.h"
#include "crossovers.h"
#include "genetic_solver.h"
#include "initializers.h"
#include "selections.h"
#include "mutations.h"
#include "translators.h"

using std::cout;
using std::endl;

using namespace GeneticAlgorithms;

#define N 50

struct MyRank {
  float operator()(const Chromosome &x) const {
    Decoder decoder(x);
    float rank = decoder.decodeFloat(N, -5.0f, 5.0f);
    return rank;
  }
};

int main() {
  std::mt19937_64 rng(12564);
  MyRank rank;
  Chromosome best = solve(10000u,
                          100u,
                          RandomInitializer(N, rng()),
                          RouletteWheelSelection<float>(rng()),
                          RandomSplitCrossOver(N, rng()),
                          RandomMutate(rng(), 0.5f),
                          rank,
                          1);
  cout << rank(best) << " " << best.gens() << endl;
  return 0;
}

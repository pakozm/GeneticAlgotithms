#include <iostream>
#include <random>
#include <vector>

#include "chromosome.h"
#include "crossovers.h"
#include "genetic_solver.h"
#include "initializers.h"
#include "selections.h"
#include "mutations.h"
#include "translators.h"

using namespace std;

using namespace GeneticAlgorithms;

#define N 50
#define Q 5.0f
#define MAX_B 5.0f
#define MAX_W 1.0f

// benefit, weight
typedef pair<float, float> object_t;

struct MyRank {
  MyRank(const vector<object_t> &objects, float q) :
    _objects(objects),
    _Q(q) {
  }
  float operator()(const Chromosome<N> &x) const {
    float W = 0.0f;
    float B = 0.0f;
    for (size_t i=0u; i<x.size() && W < _Q; ++i) {
      if (x[i]) {
        B += _objects[i].first;
        W += _objects[i].second;
      }
    }
    if (W > _Q) return 0.0f;
    else return B;
  }
  vector<object_t> _objects;
  float _Q;
};

int main() {
  vector<object_t> objects(N);
  std::mt19937_64 rng(12564);
  std::uniform_real_distribution<float> b_dist(0.0f, MAX_B);
  std::uniform_real_distribution<float> w_dist(0.0f, MAX_W);

  for (size_t i=0; i<N; ++i) {
    float b = b_dist(rng);
    float w = w_dist(rng);
    objects[i] = make_pair(b, w);
  }
  
  MyRank rank(objects, Q);
  Chromosome<N> best = solve<N>(1000u,
                                1000u,
                                RandomInitializer<N>(rng(), 0.1f),
                                RankDistSelection<N>(rng()),
                                RandomSplitCrossOver<N>(rng()),
                                RandomMutate<N>(rng(), 0.01f),
                                rank,
                                1);  
  float w = 0.0f;
  for (size_t i=0; i<best.size(); ++i) {
    if (best[i]) w += objects[i].second;
  }

  cout << best.rank() << " " << w << " " << best.gens() << endl;
  return 0;
}

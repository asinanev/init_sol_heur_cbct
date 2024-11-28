#ifndef PLANT_PROP_H
#define PLANT_PROP_H

#include <hill_climbing/hill_climbing.h>
#include "random_sampling/random_sampling.h"

class Individual {
public:
  Individual(Faculty& in, int seed);
  Individual(Faculty& in, const std::vector<std::vector<unsigned> > &tt);
  Individual create_offspring(Faculty& in, int nMutations, std::mt19937_64 gen) const;
  unsigned violations;
  unsigned score;
  std::vector<std::vector<unsigned> > tt;
  void update_score(Faculty& in);
  // Timetable *timetable;
  // Validator *validator;
  ~Individual();
};

class IndividualCompare {
public:
  bool operator()(const Individual& lhs, const Individual& rhs) const;
};

std::vector<std::string> propagate(Faculty& in);

#endif //PLANT_PROP_H

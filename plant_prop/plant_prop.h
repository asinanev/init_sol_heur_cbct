#ifndef PLANT_PROP_H
#define PLANT_PROP_H

#include <hill_climbing/hill_climbing.h>
#include "random_sampling/random_sampling.h"

class Individual {
public:
  Individual(Faculty& in, int _id, int seed);
  Individual(Faculty& in, int _id, const std::vector<std::vector<unsigned> > &tt);
  Individual create_offspring(Faculty& in, int nMutations, std::mt19937_64 gen, int id) const;
  int id;
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

std::vector<std::string> propagate(Faculty& in,  int seed);

#endif //PLANT_PROP_H

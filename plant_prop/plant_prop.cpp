#include "plant_prop.h"

#include <iostream>
#include <algorithm>

Individual::Individual(Faculty& in, int _id, const int seed) {
  Timetable timetable(in);
  // simple_rs(in, timetable, seed);
  accept_reject_rs(in, timetable, seed);

  id = _id;
  tt = timetable.GetTimetable();

  Validator validator(in, timetable);

  violations = validator.GetViolations();
  score = validator.GetTotalCost();
}

Individual::Individual(Faculty& in, int _id, const std::vector<std::vector<unsigned> > &_tt) {
  Timetable timetable(in);
  timetable.UpdateTimetable(_tt);
  Validator validator(in, timetable);
  id = _id;
  tt = timetable.GetTimetable();
  violations = validator.GetViolations();
  score = validator.GetTotalCost();
}

Individual Individual::create_offspring(Faculty& in, const int nMutations, std::mt19937_64 gen, int id) const {
  std::uniform_int_distribution<unsigned> stepTypes(0, 1);

  std::vector temp_tt(tt);
  for (int i = 0; i < nMutations; i++) {
    makeStep(in, temp_tt, gen, stepTypes(gen));
  }

  return Individual(in, id, temp_tt);
}

void Individual::update_score(Faculty& in) {
  Timetable timetable(in);
  timetable.UpdateTimetable(tt);
  Validator validator(in, timetable);
  violations = validator.GetViolations();
  score = validator.GetTotalCost();
}

Individual::~Individual() = default;

bool IndividualCompare::operator()(const Individual& lhs, const Individual& rhs) const {
  unsigned lhs_weighted_score = lhs.violations * 100;
  lhs_weighted_score += lhs.score;

  unsigned rhs_weighted_score = rhs.violations * 100;
  rhs_weighted_score += rhs.score;

  return lhs_weighted_score < rhs_weighted_score;
}

std::vector<std::string> propagate(Faculty& in,  int seed) {
  std::vector<std::string> results;

  std::vector<Individual> individuals;
  individuals.reserve(40);

  std::uniform_int_distribution<unsigned> seeds(0, 999999);

  std::mt19937_64 gen(seed);

  for (int i = 0; i < 40; i++) {
    individuals.emplace_back(in, i, seeds(gen));
  }

  for (const auto & individual : individuals) {
    std::string result = std::to_string(individual.id);
    result.append(", ");
    result.append(std::to_string(individual.violations));
    result.append(", ");
    result.append(std::to_string(individual.score));

    results.push_back(result);
  }

  // std::cout << "Individuals created" << std::endl;
  std::ranges::sort(individuals, IndividualCompare());

  for (int i = 0; i < 100000; i++) {
    // std::ranges::sort(individuals, IndividualCompare());
    for (int j = 0; j < 40; j++) {
      if (j < 4) {
        Individual best_ind = individuals[j];
        for (int k = 1; k <= 10; k++) {
          // individuals.push_back(individuals[j].create_offspring(in, 5, gen));
          std::mt19937_64 generator(i+k);
          Individual temp_individual = individuals[j].create_offspring(in, 1, generator, individuals[j].id);
          if (best_ind.violations > temp_individual.violations ||
            (best_ind.violations == temp_individual.violations && temp_individual.score < best_ind.score)) {
            best_ind.tt = temp_individual.tt;
            best_ind.update_score(in);
          }
        }

        individuals[j].tt = best_ind.tt;
        individuals[j].update_score(in);
      } else {
        // individuals.push_back(individuals[j].create_offspring(in, 15, gen));
        std::mt19937_64 generator(i+j);
        Individual temp_individual = individuals[j].create_offspring(in, 3, generator, individuals[j].id);
        // std::cout << temp_individual.violations << ", " << temp_individual.score << " | " << individuals[j].violations << ", " << individuals[j].score << std::endl;
        if (individuals[j].violations > temp_individual.violations || (individuals[j].violations == temp_individual.violations && temp_individual.score < individuals[j].score)) {
          individuals[j].tt = temp_individual.tt;
          individuals[j].update_score(in);
        }
      }
    }

    std::ranges::sort(individuals, IndividualCompare());
    // individuals.erase(individuals.begin() + 40, individuals.end());
  }

  // std::cout << "Propagated individuals" << std::endl;

  for (const Individual& individual : individuals) {
    results[individual.id].append(", ");
    results[individual.id].append(std::to_string(individual.violations));
    results[individual.id].append(", ");
    results[individual.id].append(std::to_string(individual.score));
  }

  return results;
}


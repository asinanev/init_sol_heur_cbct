#include "simulated_annealing.h"
#include "../hill_climbing/hill_climbing.h"
#include <cmath>
#include <iostream>

std::vector<double> linearReheat(double startingTemp, int numberOfIterations, int epochSize) {
  std::vector<double> temperatures(numberOfIterations, startingTemp);
  double t = startingTemp;

  for (int i = 1; i < numberOfIterations; i++) {
    if (i % epochSize == 0) {
      t = t / 2;
    }

    temperatures[i] = t * (1.0 - static_cast<double>(i % epochSize) / epochSize);
  }

  return temperatures;
}

std::vector<double> geometric(double beta, double startingTemp, int numberOfIterations) {
  std::vector<double> temperatures(numberOfIterations, startingTemp);

  for (int i = 1; i < numberOfIterations; i++) {
    temperatures[i] = beta * temperatures[i - 1];
  }

  return temperatures;
}

std::vector<double> germanAndGerman(unsigned c, int numberOfIterations) {
  std::vector<double> temperatures(numberOfIterations, 0);

  for (int i = 0; i < numberOfIterations; i++) {
    temperatures[i] = static_cast<double>(c) / std::log(static_cast<double>(i) + 1.0);
  }

  return temperatures;
}

std::vector<double> generateTemperatures(int coolingSchedule, int numberOfIterations, unsigned weightedScore) {
  switch (coolingSchedule) {
    case 1:
      return germanAndGerman(50, numberOfIterations);
    case 2:
      return germanAndGerman(1, numberOfIterations);
    case 3:
      return germanAndGerman(weightedScore , numberOfIterations);
    case 4:
      return geometric(0.99999, 1000, numberOfIterations);
    case 5:
      return linearReheat(1000, numberOfIterations, 100000);
    default:
      return std::vector<double>(numberOfIterations, 0);
  }
}

// double acceptanceProb(unsigned pViolations, unsigned pScore, unsigned cViolations, unsigned cScore, double temp) {
//   int delta = static_cast<int>(pScore) - static_cast<int>(cScore);
//   delta += static_cast<int>(pViolations) - static_cast<int>(cViolations);
//   double prob = std::exp(delta/temp);
//   return prob;
// }

double acceptanceProb(const unsigned pWScore, const unsigned cWScore, const double temp) {
  const int delta = abs(static_cast<int>(pWScore) - static_cast<int>(cWScore));
  const double prob = std::exp(-delta/temp);
  return prob;
}

std::vector<std::string> simulatedAnnealing(Faculty& faculty, Timetable& timetable, Validator& validator,
                                            int seed, int steps, int coolingSchedule) {

  std::vector<std::string> score_progression(steps, "");
  std::vector<std::vector<unsigned>> prev_tt = timetable.GetTimetable();
  std::vector<std::vector<unsigned>> curr_tt = timetable.GetTimetable();

  unsigned prev_violations = validator.GetViolations();
  unsigned prev_costs = validator.GetTotalCost();
  unsigned prev_weighted_score = prev_violations * 100 + prev_costs;

  std::vector<double> temperatures = generateTemperatures(coolingSchedule, steps, prev_weighted_score);

  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<unsigned> stepTypes(0, 1);
  std::normal_distribution<double> probCheck(0.8, 0.1);

  for (unsigned i = 1; i <= steps; i++) {
    makeStep(faculty, curr_tt, gen, stepTypes(gen));
    timetable.UpdateTimetable(curr_tt);

    unsigned curr_violations = validator.GetViolations();
    unsigned curr_costs = validator.GetTotalCost();
    unsigned curr_weighted_score = curr_violations * 100 + curr_costs;

    // if (prev_violations < curr_violations  || (curr_violations == prev_violations && prev_costs < curr_costs)) {
    if (prev_weighted_score < curr_weighted_score) {
      double ndist = probCheck(gen);
      std::cout << acceptanceProb(prev_weighted_score, curr_weighted_score, temperatures[i-1]) << " " << ndist << std::endl;
      if (acceptanceProb(prev_weighted_score, curr_weighted_score, temperatures[i-1]) > ndist) {
        prev_tt = curr_tt;
        prev_violations = curr_violations;
        prev_costs = curr_costs;
        prev_weighted_score = curr_weighted_score;
      } else {
        timetable.UpdateTimetable(prev_tt);
        curr_tt = prev_tt;
      }
    } else {
      prev_tt = curr_tt;
      prev_violations = curr_violations;
      prev_costs = curr_costs;
      prev_weighted_score = curr_weighted_score;
    }

    score_progression[i].append(std::to_string(i));
    score_progression[i].append(",");
    score_progression[i].append(std::to_string(prev_violations));
    score_progression[i].append(",");
    score_progression[i].append(std::to_string(prev_costs));
    score_progression[i].append(",");
    score_progression[i].append(std::to_string(curr_violations));
    score_progression[i].append(",");
    score_progression[i].append(std::to_string(curr_costs));
    score_progression[i].append("\n");

  }

  return score_progression;
}
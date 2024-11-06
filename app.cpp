#include <iostream>
#include <validator/validator.h>
#include <random_sampling/random_sampling.h>
#include <hill_climbing/hill_climbing.h>
#include <simulated_annealing/simulated_annealing.h>

const std::vector<int> SEEDS({
  1,
  // 2,
  // 3,
  // 4,
  // 5,
  // 6,
  // 7,
  // 8,
  // 9,
  // 10,
  // 11
});

const std::vector<std::string> FILE_PATHS({
    "../datasets/dataset1.ctt",
    // "../datasets/dataset2.ctt",
    // "../datasets/dataset3.ctt",
    // "../datasets/dataset4.ctt",
    // "../datasets/dataset5.ctt",
    // "../datasets/dataset6.ctt",
    // "../datasets/dataset7.ctt",
    // "../datasets/dataset8.ctt",
    // "../datasets/dataset9.ctt",
    // "../datasets/dataset10.ctt",
    // "../datasets/dataset11.ctt",
    // "../datasets/dataset12.ctt",
    // "../datasets/dataset13.ctt",
    // "../datasets/dataset14.ctt",
    // "../datasets/dataset15.ctt",
    // "../datasets/dataset16.ctt",
    // "../datasets/dataset17.ctt",
    // "../datasets/dataset18.ctt",
    // "../datasets/dataset19.ctt",
    // "../datasets/dataset20.ctt",
    // "../datasets/dataset21.ctt"
  });

void RandomSamplingSetup() {
  std::cout << "Random Sampling" << std::endl;
  // for (int i = 0; i < FILE_PATHS.size(); i++) {
  //   Faculty input(FILE_PATHS[i]);
  //   Timetable output(input);
  //   Validator validator(input, output);
  //
  //   std::string result_path = "results/simple_rs/solutionset";
  //   result_path.append(std::to_string(i+1));
  //   result_path.append(".csv");
  //   std::ofstream csv;
  //   csv.open(result_path);
  //
  //   csv << "seed,violations,score" << std::endl;
  //
  //   for (int j = 0; j < 100000; j++) {
  //
  //     simple_rs(input, output, j);
  //     unsigned violations = validator.GetViolations();
  //     unsigned costs = validator.GetTotalCost();
  //
  //     csv << j << "," << violations << "," << costs << std::endl;
  //   }
  //
  //   csv.close();
  //
  // }
  //
  // for (int i = 0; i < FILE_PATHS.size(); i++) {
  //   Faculty input(FILE_PATHS[i]);
  //   Timetable output(input);
  //   Validator validator(input, output);
  //
  //   std::string result_path = "results/accept_reject_rs/solutionset";
  //   result_path.append(std::to_string(i+1));
  //   result_path.append(".csv");
  //   std::ofstream csv;
  //   csv.open(result_path);
  //
  //   csv << "seed,violations,score" << std::endl;
  //
  //   for (int j = 0; j < 100000; j++) {
  //
  //     accept_reject_rs(input, output, j);
  //
  //     unsigned violations = validator.GetViolations();
  //     unsigned costs = validator.GetTotalCost();
  //
  //     csv << j << "," << violations << "," << costs << std::endl;
  //   }
  //
  //   csv.close();
  //
  // }
  //
  // for (int i = 0; i < FILE_PATHS.size(); i++) {
  //   Faculty input(FILE_PATHS[i]);
  //   Timetable output(input);
  //   Validator validator(input, output);
  //
  //   std::string result_path = "results/direct_rs/solutionset";
  //   result_path.append(std::to_string(i+1));
  //   result_path.append(".csv");
  //   std::ofstream csv;
  //   csv.open(result_path);
  //
  //   csv << "seed,violations,score" << std::endl;
  //
  //   for (int j = 0; j < 100000; j++) {
  //
  //     direct_rs(input, output, j);
  //
  //     unsigned violations = validator.GetViolations();
  //     unsigned costs = validator.GetTotalCost();
  //
  //     csv << j << "," << violations << "," << costs << std::endl;
  //   }
  //
  //   csv.close();
  //
  // }
}

void HillClimbingSetup() {
  std::cout << "Hill Climbing" << std::endl;
  for (int i = 0; i < FILE_PATHS.size(); i++) {
    Faculty input(FILE_PATHS[i]);
    Timetable output(input);
    Validator validator(input, output);
    std::cout << FILE_PATHS[i] << std::endl;

    std::vector<int> seeds(1, 0);

    std::srand(i);
    std::mt19937_64 gen(SEEDS[0]);
    std::uniform_int_distribution<int> dis(0, 100000);
    for (int & seed : seeds) {
      seed = dis(gen);
    }

    for (int j = 0; j < seeds.size(); j++) {
      std::string result_path = "results/hill_climb/solutionset";
      result_path.append(std::to_string(i+1));
      result_path.append("_");
      result_path.append(std::to_string(j));
      result_path.append(".csv");
      std::ofstream csv;
      csv.open(result_path);

      std::cout << result_path << std::endl;

      csv << "step,violations,score,cviolation,cscore" << std::endl;

      accept_reject_rs(input, output, seeds[j]);

      unsigned violations = validator.GetViolations();
      unsigned costs = validator.GetTotalCost();

      csv << "0," << violations << "," << costs << "," << violations << "," << costs << std::endl;

      std::vector<std::string> score_progression = hillClimb(input, output, validator, seeds[j], 1000000);

      for (const std::string & k : score_progression) {
        csv << k;
      }

      csv.close();
    }
  }
}

void SimulatedAnnealingSetup() {
  std::cout << "Simulated Annealing" << std::endl;
  for (int i = 0; i < FILE_PATHS.size(); i++) {
    Faculty input(FILE_PATHS[i]);
    Timetable output(input);
    Validator validator(input, output);
    std::cout << FILE_PATHS[i] << std::endl;

    std::vector<int> seeds(1, 0);

    std::srand(i);
    std::mt19937_64 gen(SEEDS[0]);
    std::uniform_int_distribution<int> dis(0, 100000);
    for (int & seed : seeds) {
      seed = dis(gen);
    }

    for (int j = 0; j < seeds.size(); j++) {
      std::string result_path = "results/simulated_annealing/solutionset";
      result_path.append(std::to_string(i+1));
      result_path.append("_");
      result_path.append(std::to_string(j));
      result_path.append("_5");
      result_path.append(".csv");
      std::ofstream csv;
      csv.open(result_path);

      std::cout << result_path << std::endl;

      csv << "step,violations,score,cviolation,cscore" << std::endl;

      accept_reject_rs(input, output, seeds[j]);

      unsigned violations = validator.GetViolations();
      unsigned costs = validator.GetTotalCost();

      csv << "0," << violations << "," << costs << "," << violations << "," << costs << std::endl;

      std::vector<std::string> score_progression = simulatedAnnealing(input, output, validator, seeds[j], 1000000,  5);

      for (const std::string & k : score_progression) {
        csv << k;
      }

      csv.close();
    }
  }
}

int main(int argc, char* argv[])
{
  // RandomSamplingSetup();
  // HillClimbingSetup();
  SimulatedAnnealingSetup();
  return 0;
}

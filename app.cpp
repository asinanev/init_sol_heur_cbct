#include <iostream>
#include <validator/validator.h>
#include <random_sampling/random_sampling.h>
#include <hill_climbing/hill_climbing.h>
#include <simulated_annealing/simulated_annealing.h>
#include <plant_prop/plant_prop.h>

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

const std::vector<int> FILE_INDICES({
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20
});

const std::vector<std::string> FILE_PATHS({
    "../datasets/dataset1.ctt",  // DONE
    "../datasets/dataset2.ctt",  // DONE
    "../datasets/dataset3.ctt",  // DONE
    "../datasets/dataset4.ctt",  // DONE
    "../datasets/dataset5.ctt",  // DONE
    "../datasets/dataset6.ctt",  // DONE
    "../datasets/dataset7.ctt",  // DONE
    "../datasets/dataset8.ctt",  // DONE
    "../datasets/dataset9.ctt",  // DONE
    "../datasets/dataset10.ctt", // ALL - FAILING for both rs methods
    "../datasets/dataset11.ctt", // DONE
    "../datasets/dataset12.ctt", // DONE
    "../datasets/dataset13.ctt", // DONE
    "../datasets/dataset14.ctt", // DONE
    "../datasets/dataset15.ctt", // DONE
    "../datasets/dataset16.ctt", // DONE
    "../datasets/dataset17.ctt", // DONE
    "../datasets/dataset18.ctt", // DONE
    "../datasets/dataset19.ctt", // DONE
    "../datasets/dataset20.ctt", // DONE
    "../datasets/dataset21.ctt", // DONE
  });

void RandomSamplingSetup() {
  std::cout << "Random Sampling" << std::endl;
  // SRS
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
  // ARRS
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
  // DRS
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

void HillClimbingSetup(int file_index) {
  std::cout << "Hill Climbing" << std::endl;
  for (int i = 0; i < 1; i++) {
    Faculty input(FILE_PATHS[file_index]);
    Timetable output(input);
    Validator validator(input, output);
    std::cout << FILE_PATHS[file_index] << std::endl;

    std::vector<int> seeds(11, 0);

    std::mt19937_64 gen(SEEDS[0]);
    std::uniform_int_distribution<int> dis(0, 100000);
    for (int & seed : seeds) {
      seed = dis(gen);
    }

    for (int j = 0; j < 11; j++) {
      std::string result_path = "../results/hill_climb/solutionset";
      result_path.append(std::to_string(file_index+1));
      result_path.append("_");
      result_path.append(std::to_string(j));
      result_path.append(".csv");
      std::ofstream csv;
      csv.open(result_path);

      std::cout << result_path << std::endl;

      csv << "step,violations,score,cviolation,cscore" << std::endl;

      // Pick one, either ARRS or SRS
      // simple_rs(input, output, seeds[j]);
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

void SimulatedAnnealingSetup(int file_index) {
  std::cout << "Simulated Annealing" << std::endl;
  for (int i = 0; i < 1; i++) {
    Faculty input(FILE_PATHS[file_index]);
    Timetable output(input);
    Validator validator(input, output);
    std::cout << FILE_PATHS[file_index] << std::endl;

    std::vector<int> seeds(11, 0);

    std::mt19937_64 gen(SEEDS[0]);
    std::uniform_int_distribution<int> dis(0, 100000);
    for (int & seed : seeds) {
      seed = dis(gen);
    }

    for (int j = 1; j < 22; j++) {
      for (int k = 1; k < 6; k++) {
        std::string result_path = "../results/simulated_annealing/solutionset";
        result_path.append(std::to_string(file_index+1));
        result_path.append("_");
        result_path.append(std::to_string(j));
        result_path.append("_");
        result_path.append(std::to_string(k));
        result_path.append(".csv");
        std::ofstream csv;
        csv.open(result_path);

        std::cout << result_path << std::endl;

        csv << "step,violations,score,cviolation,cscore" << std::endl;

        // Pick one, either ARRS or SRS
        accept_reject_rs(input, output, seeds[j]);
        // simple_rs(input, output, seeds[j]);

        unsigned violations = validator.GetViolations();
        unsigned costs = validator.GetTotalCost();

        csv << "0," << violations << "," << costs << "," << violations << "," << costs << std::endl;

        std::vector<std::string> score_progression = simulatedAnnealing(input, output, validator, seeds[j], 1000000,  k);

        for (const std::string & l : score_progression) {
          csv << l;
        }

        csv.close();
      }
    }
  }
}

void PlantPropSetup(int file_index) {
  std::cout << "PlantProp" << std::endl;
  std::vector<std::string> results;

  std::vector<int> seeds(11, 0);

  std::mt19937_64 gen(SEEDS[0]);
  std::uniform_int_distribution<int> dis(0, 100000);
  for (int & seed : seeds) {
    seed = dis(gen);
  }

  for (int j = 10; j < 11; j++) {
    std::string result_path = "../results/plant_prop/solutionset";
    result_path.append(std::to_string(file_index+1));
    result_path.append("_");
    result_path.append(std::to_string(j));
    result_path.append(".csv");
    std::ofstream csv;
    csv.open(result_path);

    std::cout << result_path << std::endl;

    Faculty input(FILE_PATHS[file_index]);
    results = propagate(input, seeds[j]);

    csv << "id,startviolations,startscore,finalviolation,finalscore" << std::endl;

    for (const std::string & l : results) {
      csv << l << std::endl;
    }

    csv.close();
  }
}

int main(int argc, char* argv[])
{
  // For one instance runs
  // RandomSamplingSetup();
  // HillClimbingSetup();
  // SimulatedAnnealingSetup();
  // PlantPropSetup();

  // For multiple instances runs
  // std::vector<std::thread> threads;
  // for (int i = 0; i < FILE_INDICES.size(); i++) {
  //   threads.emplace_back(HillClimbingSetup, FILE_INDICES[i]);
  // }
  //
  // for (auto & t : threads) {
  //   t.join();
  // }

  return 0;
}

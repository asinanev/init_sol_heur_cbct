#include <iostream>
#include <validator/validator.h>
#include <random_sampling/random_sampling.h>

void RandomSamplingSetup() {
  std::vector<std::string> file_paths({
    "../datasets/dataset1.ctt",
    "../datasets/dataset2.ctt",
    "../datasets/dataset3.ctt",
    "../datasets/dataset4.ctt",
    "../datasets/dataset5.ctt",
    "../datasets/dataset6.ctt",
    "../datasets/dataset7.ctt",
    "../datasets/dataset8.ctt",
    "../datasets/dataset9.ctt",
    "../datasets/dataset10.ctt",
    "../datasets/dataset11.ctt",
    "../datasets/dataset12.ctt",
    "../datasets/dataset13.ctt",
    "../datasets/dataset14.ctt",
    "../datasets/dataset15.ctt",
    "../datasets/dataset16.ctt",
    "../datasets/dataset17.ctt",
    "../datasets/dataset18.ctt",
    "../datasets/dataset19.ctt",
    "../datasets/dataset20.ctt",
    "../datasets/dataset21.ctt"
  });

  // for (int i = 0; i < file_paths.size(); i++) {
  //   Faculty input(file_paths[i]);
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

  //   for (int j = 0; j < 100000; j++) {
  //
  //     simple_rs(input, output, j);
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
  // for (int i = 0; i < file_paths.size(); i++) {
  //   Faculty input(file_paths[i]);
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

  for (int i = 0; i < file_paths.size(); i++) {
    Faculty input(file_paths[i]);
    Timetable output(input);
    Validator validator(input, output);

    std::string result_path = "results/direct_rs/solutionset";
    result_path.append(std::to_string(i+1));
    result_path.append(".csv");
    std::ofstream csv;
    csv.open(result_path);

    csv << "seed,violations,score" << std::endl;

    for (int j = 0; j < 100000; j++) {

      direct_rs(input, output, j);

      unsigned violations = validator.GetViolations();
      unsigned costs = validator.GetTotalCost();

      csv << j << "," << violations << "," << costs << std::endl;
    }

    csv.close();

  }
}

int main(int argc, char* argv[])
{
  RandomSamplingSetup();

  return 0;
}

#include <iostream>
#include <validator/validator.h>
#include <random_sampling/random_sampling.h>

int main(int argc, char* argv[])
{
  std::string file_path = "../datasets/dataset1.ctt";

  Faculty input(file_path);
  Timetable output(input);
  Validator validator(input, output);

  // simple_rs(input, output, 1);
  // accept_reject_rs(input, output, 1);
  direct_rs(input, output, 1);

  validator.PrintViolations(std::cout);
  std::cout << std::endl;
  validator.PrintCosts(std::cout);
  std::cout << std::endl;
  if (output.Warnings() > 0)
    std::cout << "There are " << output.Warnings() << " warnings!" << std::endl;
  std::cout << "Summary: ";
  validator.PrintTotalCost(std::cout);

  return 0;
}

#include <iostream>
#include <validator/validator.h>

int main(int argc, char* argv[])
{
  std::string file_path = "../datasets/dataset1.ctt";

  Faculty input(file_path);
  Timetable output(input);
  Validator validator(input, output);

  std::cout << input.CourseVector(0).Name() << std::endl;

  return 0;
}

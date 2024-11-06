#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H

#include <validator/validator.h>
#include <random>

std::vector<std::string> hillClimb(Faculty& faculty, Timetable& timetable, Validator& validator, int seed, int steps);
void makeStep(Faculty& faculty, std::vector<std::vector<unsigned>>& tt, std::mt19937_64 gen, unsigned stepType);

#endif //HILL_CLIMBING_H

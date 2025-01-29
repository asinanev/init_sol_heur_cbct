#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <validator/validator.h>

std::vector<std::string> simulatedAnnealing(Faculty& faculty, Timetable& timetable, Validator& validator, int seed, int steps, int cooldownSchedule);

#endif //SIMULATED_ANNEALING_H

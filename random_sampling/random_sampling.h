#ifndef RANDOM_SAMPLING_H
#define RANDOM_SAMPLING_H

#include <validator/validator.h>

void simple_rs(Faculty& faculty, Timetable& timetable, int seed);
void accept_reject_rs(Faculty& faculty, Timetable& timetable, int seed);
void direct_rs(Faculty& faculty, Timetable& timetable, int seed);

#endif //RANDOM_SAMPLING_H

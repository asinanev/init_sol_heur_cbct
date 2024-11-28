#include "hill_climbing.h"

#include <iostream>

void makeStep(Faculty& faculty, std::vector<std::vector<unsigned>>& tt, std::mt19937_64 gen, unsigned stepType) {

  if (stepType == 0) {
    std::uniform_int_distribution<unsigned> coursesDis(0, tt.size() - 1);
    const unsigned first_course_index_to_swap = coursesDis(gen);

    std::uniform_int_distribution<unsigned> courseOnePeriodDis(0, tt[first_course_index_to_swap].size() - 1);
    unsigned first_period_to_swap = courseOnePeriodDis(gen);

    while (tt[first_course_index_to_swap][first_period_to_swap] == 0)
      first_period_to_swap = courseOnePeriodDis(gen);

    const unsigned first_course_student_num = faculty.CourseVector(static_cast<int>(first_course_index_to_swap)).Students();

    unsigned second_course_index_to_swap = coursesDis(gen);

    while (second_course_index_to_swap == first_course_index_to_swap)
      second_course_index_to_swap = coursesDis(gen);

    int second_period_to_swap = -1;

    while (second_period_to_swap == -1) {
      second_course_index_to_swap = coursesDis(gen);

      while (second_course_index_to_swap == first_course_index_to_swap)
        second_course_index_to_swap = coursesDis(gen);

      for (int i = 0; i < tt[second_course_index_to_swap].size(); i++) {
        if (faculty.RoomVector(static_cast<int>(tt[second_course_index_to_swap][i])).Capacity() >= first_course_student_num) {
          second_period_to_swap = i;
        }
      }
    }

    const unsigned first_temp_room = tt[first_course_index_to_swap][first_period_to_swap];
    const unsigned second_temp_room = tt[second_course_index_to_swap][second_period_to_swap];

    tt[first_course_index_to_swap][first_period_to_swap] = 0;
    tt[second_course_index_to_swap][second_period_to_swap] = 0;

    tt[first_course_index_to_swap][first_period_to_swap] = second_temp_room;
    tt[second_course_index_to_swap][second_period_to_swap] = first_temp_room;
  } else {
    std::uniform_int_distribution<unsigned> coursesDis(0, tt.size() - 1);
    const unsigned course_index_to_swap = coursesDis(gen);
    std::uniform_int_distribution<unsigned> periodDis(0, tt[course_index_to_swap].size() - 1);
    const unsigned first_period = periodDis(gen);
    unsigned second_period = periodDis(gen);

    while (first_period == second_period)
      second_period = periodDis(gen);

    const unsigned temp = tt[course_index_to_swap][first_period];
    tt[course_index_to_swap][first_period] = tt[course_index_to_swap][second_period];
    tt[course_index_to_swap][second_period] = temp;
  }
}

std::vector<std::string> hillClimb(Faculty& faculty, Timetable& timetable, Validator& validator, int seed, int steps) {
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<unsigned> stepTypes(0, 1);

  std::vector<std::string> score_progression(steps, "");
  std::vector<std::vector<unsigned>> prev_tt = timetable.GetTimetable();
  std::vector<std::vector<unsigned>> curr_tt = timetable.GetTimetable();

  unsigned prev_violations = validator.GetViolations();
  unsigned prev_costs = validator.GetTotalCost();
  unsigned prev_weighted_score = prev_violations * 100 + prev_costs;

  for (unsigned i = 1; i <= steps; i++) {
    makeStep(faculty, curr_tt, gen, stepTypes(gen));
    timetable.UpdateTimetable(curr_tt);

    const unsigned curr_violations = validator.GetViolations();
    const unsigned curr_costs = validator.GetTotalCost();
    unsigned curr_weighted_score = curr_violations * 100 + curr_costs;

    if (prev_violations < curr_violations  || (curr_violations == prev_violations && prev_costs < curr_costs)) {
      timetable.UpdateTimetable(prev_tt);
      curr_tt = prev_tt;
    } else {
      prev_tt = curr_tt;
      prev_violations = curr_violations;
      prev_costs = curr_costs;
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
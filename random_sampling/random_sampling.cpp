#include "random_sampling.h"
#include <iostream>

void simple_rs(Faculty& faculty, Timetable& timetable, int seed) {

  std::vector<std::vector<unsigned> > rs_tt(faculty.Courses(), std::vector<unsigned>(faculty.Periods(),0));
  std::vector<unsigned> courses_to_be_scheduled;

  // Create a vector of all events that need to be scheduled
  for (int i = 0; i < faculty.Courses(); i++) {
    for (int j = 0; j < faculty.CourseVector(i).Lectures(); j++) {
       courses_to_be_scheduled.push_back(i);
    }
  }

  // Assign a random room to a random period for a random event
  std::srand(seed);
  while (courses_to_be_scheduled.size() > 0) {
    int course_id = courses_to_be_scheduled[std::rand() % courses_to_be_scheduled.size()];
    int room_id = std::rand() % faculty.Rooms();
    int period_id = std::rand() % faculty.Periods();

    rs_tt[course_id][period_id] = room_id;

    // Remove event from list of events to be scheduled
    auto it = std::find(courses_to_be_scheduled.begin(), courses_to_be_scheduled.end(),
                        course_id);
    if (it != courses_to_be_scheduled.end()) {
      courses_to_be_scheduled.erase(it);
    }
  }

  timetable.UpdateTimetable(rs_tt);
}

void accept_reject_rs(Faculty& faculty, Timetable& timetable, int seed){
  }

void direct_rs(Faculty& faculty, Timetable& timetable, int seed) {
  }
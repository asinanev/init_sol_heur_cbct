#include "random_sampling.h"
#include <iostream>
#include <set>
#include <random>

bool CurriculumConflict(Faculty& faculty, unsigned course_id, unsigned period_id, std::vector<std::vector<unsigned> > rs_tt) {
  bool flag = false;
  unsigned false_negative = rand() % 100;
  if (false_negative == 0)
    return false;

  for (int i = 0; i < rs_tt.size(); i++) {
    if (course_id != i && rs_tt[i][period_id] != 0 && faculty.Conflict(course_id, i)) {
      flag = faculty.Conflict(course_id, i);
      continue;
    }
  }
  return flag;
}

bool NotBigEnough(Faculty& faculty, std::vector<std::string> free_rooms, int student_number){
  unsigned false_negative = rand() % 50;
  if (false_negative == 0)
    return false;

  for (int i = 0; i < free_rooms.size(); i++) {
    if (faculty.RoomVector(faculty.RoomIndex(free_rooms[i])).Capacity() >= student_number)
      return false;
  }

  return true;
}

void simple_rs(Faculty& faculty, Timetable& timetable, int seed) {

  std::vector<std::vector<unsigned> > rs_tt(faculty.Courses(), std::vector<unsigned>(faculty.Periods(),0));

  // Create a vector of all events that need to be scheduled
  std::vector<unsigned> events_to_be_scheduled;
  for (int i = 0; i < faculty.Courses(); i++) {
    for (int j = 0; j < faculty.CourseVector(i).Lectures(); j++) {
       events_to_be_scheduled.push_back(i);
    }
  }

  // Assign a random room to a random period for a random event
  std::srand(seed);
  while (events_to_be_scheduled.size() > 0) {
    int course_id = events_to_be_scheduled[std::rand() % events_to_be_scheduled.size()];
    int room_id = (std::rand() % faculty.Rooms()) + 1;
    int period_id = std::rand() % faculty.Periods();

    rs_tt[course_id][period_id] = room_id;

    // Remove event from list of events to be scheduled
    auto it = std::find(events_to_be_scheduled.begin(), events_to_be_scheduled.end(),
                        course_id);
    if (it != events_to_be_scheduled.end()) {
      events_to_be_scheduled.erase(it);
    }
  }

  timetable.UpdateTimetable(rs_tt);
}

void accept_reject_rs(Faculty& faculty, Timetable& timetable, int seed){

  std::vector<std::vector<unsigned> > rs_tt(faculty.Courses(), std::vector<unsigned>(faculty.Periods(),0));

  // Create a vector of all events that need to be scheduled
  std::vector<unsigned> events_to_be_scheduled;
  for (int i = 0; i < faculty.Courses(); i++) {
    for (int j = 0; j < faculty.CourseVector(i).Lectures(); j++) {
      events_to_be_scheduled.push_back(i);
    }
  }

  // Free rooms per period
  std::vector<std::vector<std::string> > free_rooms(faculty.Periods(), std::vector<std::string>(faculty.Rooms(),""));
  for (int i = 0; i < faculty.Periods(); i++) {
    for (int j = 1; j <= faculty.Rooms(); j++) {
      free_rooms[i][j - 1] = faculty.RoomVector(j).Name();
    }
  }

  std::srand(seed);
  while (events_to_be_scheduled.size() > 0) {
    int course_id = events_to_be_scheduled[std::rand() % events_to_be_scheduled.size()];
    int period_id = std::rand() % faculty.Periods();

    while (rs_tt[course_id][period_id] != 0 || free_rooms[period_id].size() == 0) {
      period_id = std::rand() % faculty.Periods();
    }

    int room_id = faculty.RoomIndex(free_rooms[period_id][std::rand() % free_rooms[period_id].size()]);

    // Remove event from list of events to be scheduled
    auto course_it = std::find(events_to_be_scheduled.begin(), events_to_be_scheduled.end(),
                        course_id);
    if (course_it != events_to_be_scheduled.end()) {
      events_to_be_scheduled.erase(course_it);
    }

    // Remove used room from list of free rooms per period
    auto room_it = std::find(free_rooms[period_id].begin(), free_rooms[period_id].end(),
                             faculty.RoomVector(room_id).Name());
    if (room_it != free_rooms[period_id].end()) {
      free_rooms[period_id].erase(room_it);
    }

    rs_tt[course_id][period_id] = room_id;
  }

  timetable.UpdateTimetable(rs_tt);
}

void direct_rs(Faculty& faculty, Timetable& timetable, int seed) {
  std::vector<std::vector<unsigned> > rs_tt(faculty.Courses(), std::vector<unsigned>(faculty.Periods(),0));

  std::vector<unsigned> events_to_be_scheduled;
  for (int i = 0; i < faculty.Courses(); i++) {
    for (int j = 0; j < faculty.CourseVector(i).Lectures(); j++) {
      events_to_be_scheduled.push_back(i);
    }
  }

  std::vector<std::vector<std::string> > free_rooms(faculty.Periods(), std::vector<std::string>(faculty.Rooms(),""));
  for (int i = 0; i < faculty.Periods(); i++) {
    for (int j = 1; j <= faculty.Rooms(); j++) {
      free_rooms[i][j - 1] = faculty.RoomVector(j).Name();
    }
  }

  std::srand(seed);
  while (events_to_be_scheduled.size() > 0) {
    int course_id = events_to_be_scheduled[std::rand() % events_to_be_scheduled.size()];

    int period_id = std::rand() % faculty.Periods();
    std::string room_name = "";

    while (rs_tt[course_id][period_id] != 0
           || free_rooms[period_id].size() == 0
           || NotBigEnough(faculty, free_rooms[period_id], faculty.CourseVector(course_id).Students())
           || !faculty.Available(course_id, period_id)
           || CurriculumConflict(faculty, course_id, period_id, rs_tt)) {
      period_id = std::rand() % faculty.Periods();
    }

    std::vector<std::string> good_rooms;

    for (int i = 0; i < free_rooms[period_id].size(); i++) {
      if (faculty.RoomVector(faculty.RoomIndex(free_rooms[period_id][i])).Capacity() >= faculty.CourseVector(course_id).Students())
        good_rooms.push_back(free_rooms[period_id][i]);
    }

    if (good_rooms.size() > 0) {
      room_name = good_rooms[std::rand() % good_rooms.size()];
    } else {
      room_name = free_rooms[period_id][std::rand() % free_rooms[period_id].size()];
    }

    // Remove event from list of events to be scheduled
    auto course_it = std::find(events_to_be_scheduled.begin(), events_to_be_scheduled.end(),
                        course_id);
    if (course_it != events_to_be_scheduled.end()) {
      events_to_be_scheduled.erase(course_it);
    }

    // Remove used room from list of free rooms per period
    auto room_it = std::find(free_rooms[period_id].begin(), free_rooms[period_id].end(),
                             room_name);
    if (room_it != free_rooms[period_id].end()) {
      free_rooms[period_id].erase(room_it);
    }

    unsigned room_id = faculty.RoomIndex(room_name);
    rs_tt[course_id][period_id] = room_id;

  }
  timetable.UpdateTimetable(rs_tt);
}

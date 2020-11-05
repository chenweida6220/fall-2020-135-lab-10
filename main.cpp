#include <iostream>
#include "time.h"
#include "movie.h"
#include "timeslot.h"

int main() {
  // Task A. Simple functions for time
  std::cout << "Time: 2:00" << std::endl << "Total Minutes: " << minutesSinceMidnight({2,0}) << std::endl;
  std::cout << std::endl;
  std::cout << "First Time: 10:30" << std::endl << "Second Time: 13:40" << std::endl << "Difference: " << minutesUntil({10,30}, {13,40}) << std::endl;

  std::cout << "----------" << std::endl << std::endl;

  // Task B. Making it more interesting
  std::cout << "Time: 8:10" << std::endl << "Add minutes: 75" << std::endl << "Final Time: " << addMinutes({8, 10}, 75).h << ":" << addMinutes({8, 10}, 75).m << std::endl;

  std::cout << "----------" << std::endl << std::endl;

  // Task C. TimeSlot ending time and printTimeSlot
  Movie movie1 = {"Back to the Future", COMEDY, 116};
  Movie movie2 = {"Black Panther", ACTION, 134};
  Movie movie3 = {"The Avengers", ACTION, 144};
  Movie movie4 = {"Spider-Man 3", ACTION, 156};

  TimeSlot morning = {movie1, {9, 15}};
  TimeSlot daytime = {movie2, {12, 15}};
  TimeSlot evening = {movie2, {16, 45}};
  TimeSlot afterschool = {movie3, {15, 0}};
  TimeSlot sunday = {movie2, {8, 25}};

  std::cout << getTimeSlot(morning) << std::endl;
  std::cout << getTimeSlot(daytime) << std::endl;
  std::cout << getTimeSlot(evening) << std::endl;
  std::cout << getTimeSlot(afterschool) << std::endl;
  std::cout << getTimeSlot(sunday) << std::endl;

  std::cout << "----------" << std::endl << std::endl;

  // Task D. Scheduling X after Y?
  Movie movie5 = {"Spider-Man: Homecoming", ACTION, 133};
  TimeSlot breakTime = {movie5, {6, 15}};
  std:: cout << "End time for movie: 8:28" << std::endl;
  std::cout << "Start time for new movie: " << scheduleAfter(breakTime, movie5).startTime.h
  << ":" << scheduleAfter(breakTime, movie5).startTime.m << std::endl;

  std::cout << "----------" << std::endl << std::endl;

  // Task E. Overlapping time slots?
  Movie fakeMovie1 = {"Fake Movie 1", ACTION, 120};
  TimeSlot e1 = {fakeMovie1, {6, 15}};
  TimeSlot e2 = {fakeMovie1, {8, 15}};
  TimeSlot e3 = {fakeMovie1, {7, 15}};

  std::cout << "TimeSlot 1 Time: " << e1.startTime.h << ":" << e1.startTime.m << std::endl;
  std::cout << "Movie Duration: " << fakeMovie1.duration << std::endl;
  std::cout << "TimeSlot 2 Time: " << e2.startTime.h << ":" << e2.startTime.m << std::endl;
  std::cout << "Overlap: " << timeOverlap(e1, e2) << std::endl;

  std::cout << "----------" << std::endl << std::endl;
}

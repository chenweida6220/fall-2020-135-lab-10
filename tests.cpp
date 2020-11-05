#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "time.h"
#include "movie.h"
#include "timeslot.h"

// Task A. Simple functions for time
TEST_CASE("testing minutesSinceMidnight") {
  CHECK(minutesSinceMidnight({4,0}) == 240);
  CHECK(minutesSinceMidnight({0,0}) == 0);
  CHECK(minutesSinceMidnight({-4,-4}) == -244);
  CHECK(minutesSinceMidnight({4,-4}) == 236);
  CHECK(minutesSinceMidnight({-4,4}) == -236);
}

TEST_CASE("testing minutesUntil") {
  CHECK(minutesUntil({3,30}, {4,30}) == 60);
  CHECK(minutesUntil({4,30}, {3,30}) == -60);
  CHECK(minutesUntil({2,00}, {2,00}) == 0);
  CHECK(minutesUntil({0,00}, {0,00}) == 0);
}

// Task B. Making it more interesting
TEST_CASE("testing addMinutes") {
  CHECK(addMinutes({3,25}, 80).h == 4);
  CHECK(addMinutes({3,25}, 80).m == 45);

  CHECK(addMinutes({3,25}, 5).h == 3);
  CHECK(addMinutes({3,25}, 5).m == 30);

  CHECK(addMinutes({3,25}, 0).h == 3);
  CHECK(addMinutes({3,25}, 0).m == 25);

  CHECK(addMinutes({3,25}, -120).h == 1);
  CHECK(addMinutes({3,25}, -10).m == 15);

  CHECK(addMinutes({1,0}, 1440).h == 1);
  CHECK(addMinutes({1,0}, 1440).m == 0);

  CHECK(addMinutes({1,0}, 2880).h == 1);
  CHECK(addMinutes({1,0}, 2880).m == 0);

  CHECK(addMinutes({1,0}, 3000).h == 3);
  CHECK(addMinutes({1,0}, 3000).m == 0);
}

// Task C. TimeSlot ending time and printTimeSlot
TEST_CASE("testing getTimeSlot") {
  Movie movie1 = {"Spider-Man: Homecoming", ACTION, 133};
  TimeSlot saturday = {movie1, {6, 15}};
  CHECK(getTimeSlot(saturday) == "Spider-Man: Homecoming ACTION (133 min) [starts at 6:15, ends by 8:28]");

  Movie movie2 = {"Thor: Ragnarok", COMEDY, 130};
  TimeSlot sunday = {movie2, {9, 59}};
  CHECK(getTimeSlot(sunday) == "Thor: Ragnarok COMEDY (130 min) [starts at 9:59, ends by 12:09]");

  Movie fakeMovie = {"Fake Movie", DRAMA, 0};
  TimeSlot fake = {fakeMovie, {0, 0}};
  CHECK(getTimeSlot(fake) == "Fake Movie DRAMA (0 min) [starts at 0:00, ends by 0:00]");

  Movie fakeMovie2 = {"Fake Movie 2", ROMANCE, 0};
  TimeSlot fake2 = {fakeMovie2, {0, 2}};
  CHECK(getTimeSlot(fake2) == "Fake Movie 2 ROMANCE (0 min) [starts at 0:02, ends by 0:02]");

  Movie fakeMovie3 = {"Fake Movie 3", THRILLER, -5};
  TimeSlot fake3 = {fakeMovie3, {-2, -8}};
  CHECK(getTimeSlot(fake3) == "Fake Movie 3 THRILLER (-5 min) [starts at -2:-8, ends by -2:-13]");
}

// Task D. Scheduling X after Y?
TEST_CASE("testing scheduleAfter") {
  Movie movie1 = {"Back to the Future", COMEDY, 116};
  TimeSlot morning = {movie1, {9, 15}};
  CHECK(scheduleAfter(morning, movie1).startTime.h == 11);
  CHECK(scheduleAfter(morning, movie1).startTime.m == 11);

  Movie movie2 = {"Black Panther", ACTION, 134};
  TimeSlot daytime = {movie2, {12, 15}};
  CHECK(scheduleAfter(daytime, movie2).startTime.h == 14);
  CHECK(scheduleAfter(daytime, movie2).startTime.m == 29);

  Movie fakeMovie = {"Fake Movie", DRAMA, 0};
  TimeSlot fake = {fakeMovie, {0, 0}};
  CHECK(scheduleAfter(fake, fakeMovie).startTime.h == 0);
  CHECK(scheduleAfter(fake, fakeMovie).startTime.m == 0);

  Movie fakeMovie2 = {"Fake Movie 2", THRILLER, -2};
  TimeSlot fake2 = {fakeMovie2, {0, -1}};
  CHECK(scheduleAfter(fake2, fakeMovie2).startTime.h == 0);
  CHECK(scheduleAfter(fake2, fakeMovie2).startTime.m == -3);
}

// Task E. Overlapping time slots?
TEST_CASE("testing timeOverlap") {
  Movie fakeMovie = {"Fake Movie", ACTION, 120};
  TimeSlot e1 = {fakeMovie, {6, 15}};
  TimeSlot e2 = {fakeMovie, {8, 15}};
  TimeSlot e3 = {fakeMovie, {7, 15}};

  CHECK(timeOverlap(e1,e2) == 0);
  CHECK(timeOverlap(e1,e3) == 1);
  CHECK(timeOverlap(e2,e3) == 1);
  CHECK(timeOverlap(e2,e1) == 0);
  CHECK(timeOverlap(e3,e2) == 1);
  CHECK(timeOverlap(e3,e1) == 1);
  CHECK(timeOverlap(e1,e1) == 1);
}

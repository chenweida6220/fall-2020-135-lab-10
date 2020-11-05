#include <iostream>
#include <sstream>
#include "time.h"
#include "movie.h"
#include "timeslot.h"

// Task A. Simple functions for time
int minutesSinceMidnight(Time time) {
  int minutes = 0;
  minutes = (time.h * 60) + time.m;
  return minutes;
}


int minutesUntil(Time earlier, Time later) {
  int earlierMinutes = (earlier.h * 60) + earlier.m;
  int laterMinutes = (later.h * 60) + later.m;

  return laterMinutes - earlierMinutes;
}

// Task B. Making it more interesting
Time addMinutes(Time time0, int min) {
  int time0Minutes = (time0.h * 60) + time0.m;
  time0Minutes += min;

  // 1440 minutes in a day
  while (time0Minutes > 1440) {
    time0Minutes -= 1440;
  }

  time0.h = time0Minutes/60;
  time0.m = time0Minutes%60;

  return time0;
}

// Task C. TimeSlot ending time and printTimeSlot
std::string printMovie(Movie mv) {
    std::string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    std::string duration = std::to_string(mv.duration);
    std::string movie = mv.title + " " + g + " (" + duration + " min)";
    return movie;
}

std::string getTimeSlot(TimeSlot ts) {
  std::stringstream ss;
  // add 0 after semicolon if starttime and endtime m is single-digit
  if ((addMinutes(ts.startTime, ts.movie.duration).m >= 0 && addMinutes(ts.startTime, ts.movie.duration).m < 10)
  && (ts.startTime.m >= 0 && ts.startTime.m < 10))  {
    ss << printMovie(ts.movie) << " [starts at " << ts.startTime.h << ":0" << ts.startTime.m << ", ends by "
    << addMinutes(ts.startTime, ts.movie.duration).h << ":0" << addMinutes(ts.startTime, ts.movie.duration).m << "]";
    return ss.str();
  }
  // add 0 after semicolon if endtime m is single-digit
  else if (addMinutes(ts.startTime, ts.movie.duration).m >= 0 && addMinutes(ts.startTime, ts.movie.duration).m < 10)  {
    ss << printMovie(ts.movie) << " [starts at " << ts.startTime.h << ":" << ts.startTime.m << ", ends by "
    << addMinutes(ts.startTime, ts.movie.duration).h << ":0" << addMinutes(ts.startTime, ts.movie.duration).m << "]";
    return ss.str();
  }
  // add 0 after semicolon if starttime m is single-digit
  else if (ts.startTime.m >= 0 && ts.startTime.m < 10)  {
    ss << printMovie(ts.movie) << " [starts at " << ts.startTime.h << ":0" << ts.startTime.m << ", ends by "
    << addMinutes(ts.startTime, ts.movie.duration).h << ":" << addMinutes(ts.startTime, ts.movie.duration).m << "]";
    return ss.str();
  }

  ss << printMovie(ts.movie) << " [starts at " << ts.startTime.h << ":" << ts.startTime.m << ", ends by "
  << addMinutes(ts.startTime, ts.movie.duration).h << ":" << addMinutes(ts.startTime, ts.movie.duration).m << "]";
  return ss.str();
}

// Task D. Scheduling X after Y?
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie) {
  int endTimeInMinutes = (addMinutes(ts.startTime, ts.movie.duration).h * 60) + addMinutes(ts.startTime, ts.movie.duration).m;
  TimeSlot newSlot = {nextMovie, {endTimeInMinutes/60, endTimeInMinutes%60}};
  return newSlot;
}

// Task E. Overlapping time slots?
bool timeOverlap(TimeSlot ts1, TimeSlot ts2) {
  bool ts1First;
  // if they start at the same time
  if (minutesUntil(ts1.startTime, ts2.startTime) == 0) {
    ts1First = true;
    return ts1First;
  }
  // ts1 is bigger
  else if (minutesUntil(ts1.startTime, ts2.startTime) < 0) {
    ts1First = true;
  }
  // ts2 is bigger
  else if (minutesUntil(ts1.startTime, ts2.startTime) > 0) {
    ts1First = false;
  }

  // if ts1 is bigger
  if (ts1First == true) {
    Time endTime = addMinutes(ts2.startTime, ts2.movie.duration);
    // endTime of ts2 is equal to startTime of ts1
    if (minutesUntil(endTime, ts1.startTime) == 0) {
      return false;
    }
    // endTime of ts2 is greater than startTime of ts1
    else if (minutesUntil(endTime, ts1.startTime) < 0) {
      return true;
    }
    // endTime of ts2 is smaller than startTime of ts1
    else if (minutesUntil(endTime, ts1.startTime) > 0) {
      return false;
    }
  }
  // if ts2 is bigger
  else if (ts1First == false) {
    Time endTime = addMinutes(ts1.startTime, ts1.movie.duration);
    // endTime of ts1 is equal to startTime of ts2
    if (minutesUntil(endTime, ts2.startTime) == 0) {
      return false;
    }
    // endTime of ts1 is greater than startTime of ts2
    else if (minutesUntil(endTime, ts2.startTime) < 0) {
      return true;
    }
    // endTime of ts1 is smaller than startTime of ts2
    else if (minutesUntil(endTime, ts2.startTime) > 0) {
      return false;
    }
  }
  return false;
}

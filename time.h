#pragma once

class Time {
public:
    int h;
    int m;
};

int minutesSinceMidnight(Time time);
int minutesUntil(Time earlier, Time later);
Time addMinutes(Time time0, int min);

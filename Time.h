#ifndef EXPERTCPP_EX2_TIME_H
#define EXPERTCPP_EX2_TIME_H
#include <map>
#include <iostream>

using namespace std;

#define MINUTES_PER_HOUR 60
#define MINUTES_PER_DAY 24*MINUTES_PER_HOUR


class Time {
private:
    int month, day, hours, minutes;

public:
    Time(int d, int m,int hour ,int min);
    int minutesSinceTime(const Time& start_time) const;
    bool operator > (const Time& other) const;
    string toString() const;

};

class OlderTime{
public:
    bool operator() (const pair<Time,int>& p1, const pair<Time,int>& p2) const{
        //returns true if time of p1 is older than time of p2;
        return p1.first > p2.first;
    }
};

bool isLegalTime(int,int, int, int);

#endif //EXPERTCPP_EX2_TIME_H

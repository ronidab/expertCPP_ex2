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
    Time(int m, int d,int hour ,int min);
    int minutesSinceTime(const Time& start_time);
    string toString() const;

};
////global function
//bool isLegalTime(int month, int day, int hours, int minutes){
//    if(month < 1 || month > 12){
//        return false;
//    }
//    if(day < 0){return false;}
//    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
//        if(day > 31){return false;}
//    }
//    else if(month == 2){
//        if(day > 28){ return false;}
//    }
//    else if(month == 4 || month == 6 || month == 9 || month == 11){
//        if(day > 30){ return false;}
//    }
//    return true;
//}

#endif //EXPERTCPP_EX2_TIME_H

//
// Created by User on 21/05/2021.
//

#include "Time.h"

Time::Time(int d, int m,int hour ,int min):day(d),month(m),hours(hour),minutes(min){
};

string Time::toString() const{
    string t = to_string(day) + '/' + to_string(month) + ' ' + to_string(hours) + ':' + to_string(minutes);
    return t;
}

int Time::minutesSinceTime(const Time& start_time){
    map<int, int> months_dictionary;
    months_dictionary.insert(pair<int,int>(1,31));
    months_dictionary.insert(pair<int,int>(2,28));
    months_dictionary.insert(pair<int,int>(3,31));
    months_dictionary.insert(pair<int,int>(4,30));
    months_dictionary.insert(pair<int,int>(5,31));
    months_dictionary.insert(pair<int,int>(6,30));
    months_dictionary.insert(pair<int,int>(7,31));
    months_dictionary.insert(pair<int,int>(8,31));
    months_dictionary.insert(pair<int,int>(9,30));
    months_dictionary.insert(pair<int,int>(10,31));
    months_dictionary.insert(pair<int,int>(11,30));
    months_dictionary.insert(pair<int,int>(12,31));

    int total_minutes = 0;
    //1.calculate days per months between shipping:         //start: 11/01 10:01         this: 15/03 19:09
    int curr_month=start_time.month;

    while(curr_month!=month){
        curr_month++;
        if(curr_month==month){break;}
        total_minutes+=months_dictionary[curr_month]*MINUTES_PER_DAY;
    }
    //2.calculates number of days between shipping:
    if(month != start_time.month){
        int days1 = months_dictionary[start_time.month] - start_time.day;       //days left from leaving month
        int days2 = day;        //days left from arriving month
        total_minutes += (days1+days2)*MINUTES_PER_DAY;
    }
    else{
        int days = day - start_time.day;
        total_minutes+=days*MINUTES_PER_DAY;
    }
    //3.calculates number of hours between shipping
    total_minutes += (hours - start_time.hours)*MINUTES_PER_HOUR;

    //4.calculates amount of minutes between shipping
    total_minutes += minutes - start_time.minutes;

    return total_minutes;

}
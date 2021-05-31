//
// Created by User on 21/05/2021.
//

#include "Time.h"

//global function
bool isLegalTime(int day,int month, int hours, int minutes){
    if(day < 0){return false;}
    if(month < 1 || month > 12){
        return false;
    }
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if(day > 31){return false;}
    }
    else if(month == 2){
        if(day > 28){ return false;}
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11){
        if(day > 30){ return false;}
    }
    if(hours < 0 || hours > 23){
        return false;
    }
    if(minutes < 0 || minutes > 59){
        return false;
    }
    return true;
}

Time::Time(int d, int m,int hour ,int min):day(d),month(m),hours(hour),minutes(min){
};

string Time::toString() const{
    string t = to_string(day) + '/' + to_string(month) + ' ' + to_string(hours) + ':' + to_string(minutes);
    return t;
}

int Time::minutesSinceTime(const Time& start_time) const{
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

bool Time::operator > (const Time& other) const{
    //return true if this is older than other
    // **example: this:1/6 > other:4/2 ->true
    Time start_time = Time(1,1,00,01);  //first date and hour in 2021
    return this->minutesSinceTime(start_time) > other.minutesSinceTime(start_time);
}
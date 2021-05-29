//
// Created by User on 28/05/2021.
//

#include "Terminal.h"


void Terminal::validInput(const char *file_name) const {
    ifstream file(file_name);
    if (!file) {
        throw FileError();
    } else {
        int line_num = 1;
        string line, src_name, time;
        getline(file, line);
        int first_psik_index = line.find(',');
        if (first_psik_index > 15) {
            //port name include 16 chars at the most
            throw InvalidINput(file_name, line_num);
        }
        src_name = line.substr(0, first_psik_index);
        //port name included only chars and spaces
        for (char i : src_name) {
            if (!(isalpha(i) || i == ' ')) {
                throw InvalidINput(file_name, line_num);
            }
        }

        time = line.substr(line.find(',') + 1);
        int d, m, h, min;
        if (!isLegalTime(d, m, h, min)) {
            throw InvalidINput(file_name, line_num);
        }
        string_to_time(time, d, m, h, min);
        Time start_time = Time(d, m, h, min);
        Time prev_time = start_time;

        string arrive_time, leave_time, capacity, current_name;
        line_num++;
        while (getline(file, line)) {
            int first_psik = line.find(',');
            if (first_psik_index > 15) {
                //port name include 16 chars at the most
                throw InvalidINput(file_name, line_num);
            }

            current_name = line.substr(0, first_psik);
            //port name included only chars and spaces
            for (char i : current_name) {
                if (!(isalpha(i) || i == ' ')) {
                    throw InvalidINput(file_name, line_num);
                }
            }

            int second_psik = line.find(',', first_psik + 1);
            int third_psik = line.find(',', second_psik + 1);
            arrive_time = line.substr(first_psik + 1, second_psik - first_psik - 1);
            leave_time = line.substr(third_psik + 1);

            int d, m, h, min;
            string_to_time(arrive_time, d, m, h, min);
            Time arrive_to_port_time = Time(d, m, h, min);
            string_to_time(leave_time, d, m, h, min);
            Time leave_port_time = Time(d, m, h, min);

            if (prev_time > arrive_to_port_time) {
                //start shipping time before arrive time
                throw InvalidINput(file_name, line_num);
            }
            if (arrive_to_port_time > leave_port_time) {
                //arrive time to port before leave time
                throw InvalidINput(file_name, line_num);
            }
            prev_time = leave_port_time;

            capacity = line.substr(second_psik + 1, third_psik - second_psik - 1);
            //capacity number is positive and nature
            if (capacity.find('.') != std::string::npos || capacity.find('-') != std::string::npos) {
                throw InvalidINput(file_name, line_num);
            }
            line_num++;
        }
    }

}

void Terminal::loadFile(const char* file_name){
    s.load(file_name);
}

void Terminal::run(){
    string ord_str;
    while(true){
        cin >> ord_str;

    }



}

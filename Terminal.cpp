#include "Terminal.h"

void Terminal::setOutputFile(const char *file_name) {
    s.setOutFile(file_name);
}

bool Terminal::validInput(const char *file_name, int &num) const {
    ifstream file(file_name);
    if (!file) {
        num = 0;
        return false;
    }
    int line_num = 1;
    string line, src_name, time;
    getline(file, line);
    int first_psik_index = line.find(',');
    if (first_psik_index > 15) {
        //port name include 16 chars at the most
        num = line_num;
        return false;
    }
    src_name = line.substr(0, first_psik_index);
    //port name included only chars and spaces
    for (char i : src_name) {
        if (!(isalpha(i) || i == ' ')) {
            num = line_num;
            return false;
        }
    }

    time = line.substr(line.find(',') + 1);
    int d, m, h, min;
    string_to_args(time, d, m, h, min);
    if (!isLegalTime(d, m, h, min)) {
        num = line_num;
        return false;
    }
    string_to_args(time, d, m, h, min);
    Time start_time = Time(d, m, h, min);
    Time prev_time = start_time;

    string arrive_time, leave_time, capacity, current_name;
    line_num++;
    while (getline(file, line)) {
        int first_psik = line.find(',');
        if (first_psik_index > 15) {
            //port name include 16 chars at the most
            num = line_num;
            return false;
        }

        current_name = line.substr(0, first_psik);
        //port name included only chars and spaces
        for (char i : current_name) {
            if (!(isalpha(i) || i == ' ')) {
                num = line_num;
                return false;
            }
        }

        int second_psik = line.find(',', first_psik + 1);
        int third_psik = line.find(',', second_psik + 1);
        arrive_time = line.substr(first_psik + 1, second_psik - first_psik - 1);
        leave_time = line.substr(third_psik + 1);

        int d, m, h, min;
        string_to_args(arrive_time, d, m, h, min);
        Time arrive_to_port_time = Time(d, m, h, min);
        string_to_args(leave_time, d, m, h, min);
        Time leave_port_time = Time(d, m, h, min);

        if (prev_time > arrive_to_port_time) {
            //start shipping time before arrive time
            num = line_num;
            return false;
        }
        if (arrive_to_port_time > leave_port_time) {
            //arrive time to port before leave time
            num = line_num;
            return false;
        }
        prev_time = leave_port_time;

        capacity = line.substr(second_psik + 1, third_psik - second_psik - 1);
        //capacity number is positive and nature
        if (capacity.find('.') != std::string::npos || capacity.find('-') != std::string::npos) {
            num = line_num;
            return false;
        }
        line_num++;
    }
    file.close();

    return true;

}

void Terminal::loadFile(const char *file_name) {
    s.load(file_name);
}

//load, outbound, inbound, balance, print

void Terminal::run() {
    map<string, order> ord_trns{{"load",     load},
                                {"outbound", outbound},
                                {"inbound",  inbound},
                                {"balance",  balance},
                                {"print",    print},
                                {"exit",     Exit}};
    string input_line, ord_str, first_word, second_word;
    int port_id;
    while (true) {
        getline(cin, input_line);
        if (input_line.find(',') != std::string::npos) first_word = input_line.substr(0, input_line.find(','));
         else {
            first_word = input_line.substr(0, input_line.find(' '));
        }
        if (first_word.compare("load") && first_word.compare("print") && first_word.compare("exit")) {
            second_word = input_line.substr(input_line.find(',') + 1);
            if (second_word == "outbound" || second_word == "inbound") {
                if ((port_id = s.portExist(first_word)) == -1) {
                    cerr << first_word + " does not exist in the database.\n";
                    continue;
                } else {
                    ord = ord_trns[second_word];
                    switch (ord) {
                        case outbound: {
                            s.outbound(port_id);
                            break;
                        }
                        case inbound: {
                            s.inbound(port_id);
                            break;
                        }
                    }
                }
            } else if (!second_word.substr(0, second_word.find(',')).compare("balance")) {
                if ((port_id = s.portExist(first_word)) == -1) cerr << first_word + " does not exist in the database.\n";
                else {
                    ord = balance;
                    string time = second_word.substr(second_word.find(',') + 1);
                    int d, m, h, min;
                    string_to_args(time, d, m, h, min);
                    if(!isLegalTime(d,m,h,min)){
                        cerr << "Time Illegal\n";
                        continue;;
                    }
                    s.balance(port_id, Time(d, m, h, min));
                }
            } else {
                cerr << "USAGE: 'load' <file> *or*\n"
                        "<node>, 'inbound' *or*\n"
                        "<node> 'outbound' *or*\n"
                        "<node> 'balance', dd/mm HH:mm *or*\n"
                        "'print' *or*\n"
                        "'exit' *to terminate*\n";
            }
        } else {
            ord = ord_trns[first_word];
            switch (ord) {
                case load: {
                    string load_file = input_line.substr(input_line.find(' ') + 1);
                    int line = -1;
                    if (!validInput(load_file.c_str(), line)) {
                        cerr << InvalidINput(load_file.c_str(), line).what();
                        continue;
                    }
                    s.load(load_file.c_str());
                    cout << "Update was successful.\n";
                    break;
                }
                case print: {
                    s.printGraphs();
                    break;

                }
                case Exit: {
                    exit(0);
                }
            }


        }


    }

}

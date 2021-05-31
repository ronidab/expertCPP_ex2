#ifndef EXPERTCPP_EX2_TERMINAL_H
#define EXPERTCPP_EX2_TERMINAL_H

#include "System.h"

enum order{load, outbound, inbound, balance, print,Exit};

class Terminal {
    System s;
    order ord;
public:
    bool validInput(const char* file_name, int& ) const;
    void setOutputFile(const char* file_name);
    void loadFile(const char* file_name);
    void run();
};


#endif //EXPERTCPP_EX2_TERMINAL_H

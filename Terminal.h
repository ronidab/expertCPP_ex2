#ifndef EXPERTCPP_EX2_TERMINAL_H
#define EXPERTCPP_EX2_TERMINAL_H

#include "System.h"

enum order{load, outbound, inbound, balance, print};

class Terminal {
    System s;
    order ord;
public:
    void validInput(const char* file_name) const;
    void loadFile(const char* file_name);
    void run();
};


#endif //EXPERTCPP_EX2_TERMINAL_H

//
// Created by User on 28/05/2021.
//

#ifndef EXPERTCPP_EX2_INVALIDINPUT_H
#define EXPERTCPP_EX2_INVALIDINPUT_H

using namespace std;

class InvalidINput: public exception {
public:
    virtual const char* what() const noexcept{ return "Invalid input in file <fileName> at line <numLine>.\n"}
};




#endif //EXPERTCPP_EX2_INVALIDINPUT_H

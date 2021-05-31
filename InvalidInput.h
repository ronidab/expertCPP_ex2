//
// Created by User on 28/05/2021.
//

#ifndef EXPERTCPP_EX2_INVALIDINPUT_H
#define EXPERTCPP_EX2_INVALIDINPUT_H

using namespace std;

class InvalidINput: public exception {
private:
    string file_name;
    int numLine;
    string reason;
public:
    InvalidINput(const char* name, int n):file_name(name), numLine(n){
        reason = "Invalid input in file " + file_name + " at line " + to_string(numLine)+'\n';
    };
    virtual const char* what() const noexcept{
        return reason.c_str();}
};




#endif //EXPERTCPP_EX2_INVALIDINPUT_H

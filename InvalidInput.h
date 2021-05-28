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
public:
    InvalidINput(const char* name, int n):file_name(name), numLine(n){};
    virtual const char* what() const noexcept{
        string res = "Invalid input in file " + file_name + " at line " + to_string(numLine);
        return res.c_str();}
};




#endif //EXPERTCPP_EX2_INVALIDINPUT_H

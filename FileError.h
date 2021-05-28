//
// Created by User on 28/05/2021.
//

#ifndef EXPERTCPP_EX2_FILEERROR_H
#define EXPERTCPP_EX2_FILEERROR_H

using namespace std;

class FileError: public exception {

public:
    virtual const char* what() const noexcept{ return "ERROR opening/reading the specified file.\n";}
};


#endif //EXPERTCPP_EX2_FILEERROR_H

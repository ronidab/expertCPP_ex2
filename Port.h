#ifndef EXPERTCPP_EX2_PORT_H
#define EXPERTCPP_EX2_PORT_H
#include <string>
#include <vector>
#include "Time.h"


using namespace std;
class Port {
private:
    int portID;
    string portName;
    int curr_balance;
    vector<pair <Time,int> > all_balances;

    void sortBalance();
public:
    Port(int id,string name);
    int getID(){ return portID; }
    string getPortName(){return portName;}
    void setBalance(int new_capacity, Time t);   //set curr balance and add balance with time to balance vector
    void balance(const Time& t);

};



#endif //EXPERTCPP_EX2_PORT_H

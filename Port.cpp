//
// Created by User on 21/05/2021.
//

#include "Port.h"

Port::Port(int id, string name):portID(id), portName(name),curr_balance(0),all_balances(vector<pair <Time,int>>()){}

void Port::setBalance(int new_capacity, Time t){
    curr_balance+=new_capacity;
    all_balances.push_back(pair<Time,int>(t,curr_balance));
}
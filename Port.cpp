//
// Created by User on 21/05/2021.
//

#include <algorithm>
#include "Port.h"

Port::Port(int id, string name):portID(id), portName(name),curr_balance(0),all_balances(vector<pair <Time,int>>()){}

void Port::setBalance(int new_capacity, Time t){
    curr_balance+=new_capacity;
    all_balances.push_back(pair<Time,int>(t,curr_balance));
}

void Port::sortBalance(){
    //sort map of balances bt times - from old to last
    std::sort(all_balances.begin(),all_balances.end(),OlderTime());
}

void Port::balance(const Time &t) {
    sortBalance();
    if(all_balances[0].first > t){
        cout << "0"<<endl;
        return;
    }
    auto last_balance = all_balances[0];
    for(int i=1; i<all_balances.size(); i++){
        if(all_balances[i].first > t){
            cout << last_balance.second << endl;
            break;
        }
        last_balance=all_balances[i];}
    cout << last_balance.second << endl;
}
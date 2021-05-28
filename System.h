//
// Created by User on 21/05/2021.
//

#ifndef EXPERTCPP_EX2_SYSTEM_H
#define EXPERTCPP_EX2_SYSTEM_H
#include <iostream>
#include <iterator>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "FileError.h"
#include "InvalidInput.h"

using namespace std;

static int ports_counter=0;

class System {
private:
    map<int,shared_ptr<Port>> ports_dictionary;
    Graph distanceGraph;
    Graph containersGraph;

    void validInput(const char* file_name) const;
public:
    System(): ports_dictionary(map<int,shared_ptr<Port>>()),distanceGraph(Graph()), containersGraph(Graph()){};
    int portExist(string&) const;

    void addPortToGraph(Graph& g,  int src_portID, int dst_portID, int dis_cap);
    void addPortToDictionary(const shared_ptr<Port> &p);
    void load(const char* file_name);
    void printContainersGraph();
    void printTimesGraph();
    void outbound(int port_id);
    void inbound(int port_id);
    void balance(int portID , const Time& date) const;

};

#endif //EXPERTCPP_EX2_SYSTEM_H

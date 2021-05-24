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
//#include "LinkedList.h"

using namespace std;

static int ports_counter;

class System {
private:
    map<int,Port> ports_dictionary;
    Graph distanceGraph;
    Graph containersGraph;

public:
    System(): ports_dictionary(map<int,Port>()),distanceGraph(Graph()), containersGraph(Graph()){};
    void addPort(Port& p);
    void init(const char* file_name);
    void printTimesGraph();
    void printContainersGraph();




};


#endif //EXPERTCPP_EX2_SYSTEM_H

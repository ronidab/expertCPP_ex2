//
// Created by User on 21/05/2021.
//

#ifndef EXPERTCPP_EX2_GRAPH_H
#define EXPERTCPP_EX2_GRAPH_H
#include <memory>
#include <vector>
#include "Port.h"
#include "LinkedList.h"
using namespace std;

struct Dst{
    weak_ptr<Port> port;
    vector<int> distance_or_capacity;

    Dst(weak_ptr<Port> p, vector<int>& vec):port{p},distance_or_capacity{vec}{};
    void addTimeOrCapacity(int minutesORcap){distance_or_capacity.push_back(minutesORcap);}
    int getAverageDistance() const{
        int total_dis=0;
        for(int i: distance_or_capacity){total_dis+=i;}
        return (total_dis/(int)distance_or_capacity.size());
    }
    int getToatalCapacity() const{
        int total=0;
        for(int i: distance_or_capacity){total+=i;}
        return total;
    }
};
struct Edge{
    int src;
    Dst dst;
};

class Graph {
private:
    int graph_size;
public:
    map<int,LinkedList<Dst>> graph;

    Graph();
    int getSize() const {return graph_size;}
    void addVertex(int vertex);
    void addEdge(Edge e);

};


#endif //EXPERTCPP_EX2_GRAPH_H

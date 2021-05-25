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
    Port port;
    vector<int> distance_or_capacity;

    void addTime(int minutes){distance_or_capacity.push_back(minutes);}
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
    int getSize() {return graph_size;}
    void addVertex(int vertex);
    void addEdge(Edge e);

};


#endif //EXPERTCPP_EX2_GRAPH_H

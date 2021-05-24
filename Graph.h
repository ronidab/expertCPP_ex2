//
// Created by User on 21/05/2021.
//

#ifndef EXPERTCPP_EX2_GRAPH_H
#define EXPERTCPP_EX2_GRAPH_H
#include <memory>
#include <vector>
#include "Port.h"
using namespace std;

struct Dst{
    int id;
    int distance_or_capacity;
};
struct Edge{
    int src;
    Dst dst;
};

class Graph {
private:
    int graph_size;
public:
    vector<vector<Dst>> graph;

    Graph();
    Graph(vector<Edge> const &edges, int N);
    int getSize() {return graph_size;}
    void addVertex(int vertex);
    void addEdge(Edge e);


};


#endif //EXPERTCPP_EX2_GRAPH_H

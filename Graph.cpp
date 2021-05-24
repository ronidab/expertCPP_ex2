#include <iostream>
#include "Graph.h"

Graph::Graph():graph_size(0), graph(vector<vector<Dst>>()){};

void Graph::addVertex(int vertex) {
    auto pos = graph.begin() + vertex;
    graph.insert(pos,vector<Dst>());
    graph_size++;
}

void Graph::addEdge(Edge edge){
    graph[edge.src].push_back(edge.dst);
}


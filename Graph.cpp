#include <iostream>
#include "Graph.h"

Graph::Graph() : graph_size(0), graph(map<int, LinkedList<Dst>>()) {};

void Graph::addVertex(int vertex) {
    if (graph.find(vertex)==graph.end()) {
        graph.insert(pair<int, LinkedList<Dst> >(vertex, LinkedList<Dst>()));
        graph_size++;
    }
}

void Graph::addEdge(Edge edge) {
    graph.find(edge.src)->second.add(edge.dst);
}


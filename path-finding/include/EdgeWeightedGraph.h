#pragma once

#include <vector>
#include <string>
#include "Edge.h"

class EdgeWeightedGraph {

    int v;
    int e;
    std::vector<std::vector<Edge>> adj;

public:
    EdgeWeightedGraph( int v );
    virtual ~EdgeWeightedGraph();
    int getV();
    int getE();
    void addEdge( Edge edge );
    std::vector<Edge>& getAdj( int vertex );
    std::vector<Edge> edges();
    std::string toString();

};
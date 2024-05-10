#pragma once

#include <queue>
#include <stack>
#include <vector>
#include "EdgeWeightedGraph.h"
#include "Edge.h"

class DijkstraUndirectedSP {

    std::vector<float> distTo;
    std::vector<Edge> edgeTo;
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> pq;

    void relax( Edge &e, int v );

public:
    DijkstraUndirectedSP( EdgeWeightedGraph &g, int s );
    virtual ~DijkstraUndirectedSP();
    float distToV( int v );
    bool hasPathTo( int v );
    std::stack<Edge> pathTo( int v );

};
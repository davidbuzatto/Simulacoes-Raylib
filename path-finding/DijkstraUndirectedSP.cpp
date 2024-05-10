#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
#include "DijkstraUndirectedSP.h"
#include "Edge.h"

DijkstraUndirectedSP::DijkstraUndirectedSP( EdgeWeightedGraph &g, int s ) {

    float infinity = std::numeric_limits<float>::infinity();

    for ( int i = 0; i < g.getV(); i++ ) {
        distTo.push_back( infinity );
        edgeTo.push_back( Edge( -1, -1, -1 ) );
    }
    distTo[s] = 0.0f;

    pq.push( std::make_pair( distTo[s], s ) );

    while ( !pq.empty() ) {

        std::pair<float, int> p = pq.top();
        float v = p.second;
        pq.pop();

        for ( Edge &e : g.getAdj( v ) ) {
            std::cout << e.toString() << "\n";
            relax( e, v );
        }

    }

}

DijkstraUndirectedSP::~DijkstraUndirectedSP() = default;

float DijkstraUndirectedSP::distToV( int v ) {
    return distTo[v];
}

bool DijkstraUndirectedSP::hasPathTo( int v ) {
    return distTo[v] < std::numeric_limits<float>::infinity();
}

std::stack<Edge> DijkstraUndirectedSP::pathTo( int v ) {
    
    std::stack<Edge> path;

    if ( !hasPathTo( v ) ) {
        return path;
    }

    int current = v;
    Edge &e = edgeTo[current];

    while ( e.either() != -1 ) {
        path.push( e );
        current = e.other( current );
        e = edgeTo[current];
    }

    return path;

}

void DijkstraUndirectedSP::relax( Edge &e, int v ) {
    int w = e.other( v );
    if ( distTo[w] > distTo[v] + e.getWeight() ) {
        distTo[w] = distTo[v] + e.getWeight();
        edgeTo[w] = e;
        pq.push( std::make_pair( distTo[w], w ) );
    }
}
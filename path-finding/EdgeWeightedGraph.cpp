#include <iostream>
#include <format>
#include <vector>
#include <string>
#include "EdgeWeightedGraph.h"
#include "Edge.h"

EdgeWeightedGraph::EdgeWeightedGraph( int v )
    :
    v( v ),
    e( 0 ) {
    
    for ( int i = 0; i < v; i++ ) {
        adj.emplace_back();
    }

}

EdgeWeightedGraph::~EdgeWeightedGraph() = default;

int EdgeWeightedGraph::getV() {
    return v;
}

int EdgeWeightedGraph::getE() {
    return e;
}

void EdgeWeightedGraph::addEdge( Edge edge ) {
    int v = edge.either();
    int w = edge.other( v );
    adj[v].push_back( edge );
    adj[w].push_back( edge );
    e++;
}

std::vector<Edge>& EdgeWeightedGraph::getAdj( int vertex ) {
    return adj[vertex];
}

std::vector<Edge> EdgeWeightedGraph::edges() {
    std::vector<Edge> list;
    for ( int i = 0; i < v; i++ ) {
        int selfLoops = 0;
        for ( Edge& e : adj[i] ) {
            if ( e.other( i ) > i ) {
                list.push_back( e );
            } else if ( e.other(v) == v ) {
                if ( selfLoops % 2 == 0 ) {
                    list.push_back( e );
                }
                selfLoops++;
            }
        }
    }
    return list;
}

std::string EdgeWeightedGraph::toString() {
    std::string str;
    str += std::format( "Vertices: {}\nEdges: {}\n", v, e );
    for ( size_t i = 0; i < adj.size(); i++ ) {
        if ( i != 0 ) {
            str += "\n";
        }
        str += std::format( "{}: ", i );
        for ( Edge e : adj[i] ) {
            str += e.toString() + " ";
        }
    }
    return str;
}
#include <iostream>
#include <format>
#include <string>
#include "Edge.h"

Edge::Edge( int v, int w, float weight )
    :
    v( v ),
    w( w ),
    weight( weight ) {
}

Edge::~Edge() = default;

float Edge::getWeight() {
    return weight;
}

int Edge::either() {
    return v;
}

int Edge::other( int vertex ) {
    return vertex == v ? w : v;
}

int Edge::compare( Edge& edge ) {
    if ( weight < edge.weight ) {
        return -1;
    } else if ( weight > edge.weight ) {
        return 1;
    }
    return 0;
}

std::string Edge::toString() {
    return std::format( "{}-{} {:.2f}", v, w, weight );
}
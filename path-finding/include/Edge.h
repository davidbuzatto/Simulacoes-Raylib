#pragma once

class Edge {

    int v;
    int w;
    float weight;

public:
    Edge( int v, int w, float weight );
    virtual ~Edge();
    float getWeight();
    int either();
    int other( int vertex );
    int compare( Edge& edge );

};
#pragma once

#include "NeighborhoodType.h"

class Rule {
    int source;
    int target;
    NeighborhoodType type;
    int neighbors[8];

public:
    Rule( 
        int source, 
        int n1,
        int n2,
        int n3,
        int n4,
        int n5,
        int n6,
        int n7,
        int n8,
        int target,
        NeighborhoodType type );
    ~Rule();
    bool match( int n1, int n2, int n3, int n4 );
    bool match( int n1, int n2, int n3, int n4, 
                int n5, int n6, int n7, int n8 );
    int getTarget();
    void print();
};
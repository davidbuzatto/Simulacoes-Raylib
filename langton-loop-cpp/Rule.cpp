#include <iostream>
#include "Rule.h"
#include "NeighborhoodType.h"

Rule::Rule( 
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
        NeighborhoodType type )
        :
        source( source ),
        target( target ),
        type( type ) {
    neighbors[0] = n1;
    neighbors[1] = n2;
    neighbors[2] = n3;
    neighbors[3] = n4;
    neighbors[4] = n5;
    neighbors[5] = n6;
    neighbors[6] = n7;
    neighbors[7] = n8;
}

Rule::~Rule() = default;

bool Rule::match( int n1, int n2, int n3, int n4 ) {
    int max = 4;
    for ( int i = 0; i < max; i++ ) {
        if ( n1 == neighbors[(i+0)%max] && 
             n2 == neighbors[(i+1)%max] && 
             n3 == neighbors[(i+2)%max] && 
             n4 == neighbors[(i+3)%max] ) {
            return true;
        }
    }
    return false;
}

bool Rule::match( int n1, int n2, int n3, int n4, 
                  int n5, int n6, int n7, int n8 ) {
    int max = 8;
    for ( int i = 0; i < max; i++ ) {
        if ( n1 == neighbors[(i+0)%max] && 
             n2 == neighbors[(i+1)%max] && 
             n3 == neighbors[(i+2)%max] && 
             n4 == neighbors[(i+3)%max] &&
             n5 == neighbors[(i+4)%max] && 
             n6 == neighbors[(i+5)%max] && 
             n7 == neighbors[(i+6)%max] && 
             n8 == neighbors[(i+7)%max] ) {
            return true;
        }
    }
    return false;
}

int Rule::getTarget() {
    return target;
}

void Rule::print() {
    std::cout << source;
    for ( int i = 0; i < 8; i++ ) {
        std::cout << neighbors[i];
    }
    std::cout << target;
}
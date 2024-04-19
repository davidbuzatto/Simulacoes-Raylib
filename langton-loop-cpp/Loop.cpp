#include <iostream>
#include <vector>
#include <cstring>
#include <string>

#include "Loop.h"
#include "raylib.h"

Loop::Loop( 
    int gridLength, 
    std::string initialStateFilePath, 
    std::string ruleDataFilePath, 
    NeighborhoodType ruleType,
    std::vector<Color> stateColors,
    int xOffset, 
    int yOffset  )
    :
    gridLength( gridLength ),
    ruleType( ruleType ),
    stateColors( stateColors ) {

    grid = new int[gridLength*gridLength]();
    tempGrid = new int[gridLength*gridLength]();

    parseInitialStateData( LoadFileText( initialStateFilePath.c_str() ), xOffset, yOffset );
    parseRuleData( LoadFileText( ruleDataFilePath.c_str() ) );
    
}

Loop::~Loop() {
    delete[] grid;
    delete[] tempGrid;
};

void Loop::draw() {
    
    for ( int i = 0; i < gridLength; i++ ) {
        for ( int j = 0; j < gridLength; j++ ) {
            int v = grid[i*gridLength+j];
            DrawRectangle( cellWidth * j, cellWidth * i, cellWidth, cellWidth, stateColors[v] );
        }
    }

}

void Loop::parseInitialStateData( const char* iniStateData, int xOffset, int yOffset ) {

    int line = 0;
    int column = 0;

    while ( *iniStateData != '\0' ) {

        if ( *iniStateData == '\n' ) {
            line++;
            column = 0;
        } else {
            grid[(line+yOffset)*gridLength+(column++)+xOffset] = static_cast<int>( *iniStateData ) - 48;
        }

        iniStateData++;

    }

}

void Loop::parseRuleData( const char* ruleData ) {

    while ( *ruleData != '\0' ) {
        
        std::vector<int> values;
        int quantity = 0;

        switch ( ruleType ) {
            case NeighborhoodType::VON_NEUMANN:
                quantity = 6;
                break;
            case NeighborhoodType::MOORE:
                quantity = 10;
                break;
        }

        for ( int i = 0; i < quantity; i++ ) {
            values.push_back( static_cast<int>( *ruleData ) - 48 );
            ruleData++;
        }

        switch ( ruleType ) {
            case NeighborhoodType::VON_NEUMANN:
                if ( !rules.contains( values[0] ) ) {
                    rules[values[0]] = std::vector<Rule>();
                }
                rules[values[0]].push_back( 
                    Rule( 
                        values[0], 
                        values[1], 
                        values[2], 
                        values[3], 
                        values[4],  
                        0, 0, 0, 0,
                        values[5], 
                        ruleType
                    )
                );
                break;
            case NeighborhoodType::MOORE:
                if ( !rules.contains( values[0] ) ) {
                    rules[values[0]] = std::vector<Rule>();
                }
                rules[values[0]].push_back( 
                    Rule( 
                        values[0], 
                        values[1], 
                        values[2], 
                        values[3], 
                        values[4], 
                        values[5], 
                        values[6], 
                        values[7], 
                        values[8], 
                        values[9], 
                        ruleType
                    )
                );
                break;
        }

        if ( *ruleData == '\n' ) {
            ruleData++;
        }

    }

}

void Loop::updateCellWidth( int screenWidth ) {
    cellWidth = screenWidth / gridLength;
}

void Loop::next() {

    for ( int i = 0; i < gridLength; i++ ) {
        for ( int j = 0; j < gridLength; j++ ) {

            switch ( ruleType ) {
                case NeighborhoodType::VON_NEUMANN:
                    processVonNeumannRule( i, j );
                    break;
                case NeighborhoodType::MOORE:
                    processMooreRule( i, j );
                    break;
            }
            
        }
    }

    std::memcpy( grid, tempGrid, gridLength * gridLength * sizeof( int ) );

}

void Loop::processVonNeumannRule( int line, int column ) {

    int p = line * gridLength + column;
    int up = (line-1 < 0 ? gridLength-1 : line-1) * gridLength + column;
    int down = (line+1 == gridLength ? 0 : line+1) * gridLength + column;
    int left = line * gridLength + (column-1 < 0 ? gridLength-1 : column-1);
    int right = line * gridLength + (column+1 == gridLength ? 0 : column+1);
    
    int source = grid[p];
    
    for ( Rule r : rules[source] ) {
        if ( r.match( grid[up], grid[right], grid[down], grid[left] ) ) {
            tempGrid[p] = r.getTarget();
        }
    }

}

void Loop::processMooreRule( int line, int column ) {

    int p = line * gridLength + column;
    int up = (line-1 < 0 ? gridLength-1 : line-1) * gridLength + column;
    int down = (line+1 == gridLength ? 0 : line+1) * gridLength + column;
    int left = line * gridLength + (column-1 < 0 ? gridLength-1 : column-1);
    int right = line * gridLength + (column+1 == gridLength ? 0 : column+1);

    int upRight = (line-1 < 0 ? gridLength-1 : line-1) * gridLength + (column+1 == gridLength ? 0 : column+1);
    int upLeft = (line-1 < 0 ? gridLength-1 : line-1) * gridLength + (column-1 < 0 ? gridLength-1 : column-1);
    int downRight = (line+1 == gridLength ? 0 : line+1) * gridLength + (column+1 == gridLength ? 0 : column+1);
    int downLeft = (line+1 == gridLength ? 0 : line+1) * gridLength + (column-1 < 0 ? gridLength-1 : column-1);
    
    int source = grid[p];
    
    for ( Rule r : rules[source] ) {
        if ( r.match( grid[up], grid[upRight], grid[right], grid[downRight], grid[down], grid[downLeft], grid[left], grid[upLeft] ) ) {
            tempGrid[p] = r.getTarget();
        }
    }

}
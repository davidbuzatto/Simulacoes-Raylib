#pragma once

#include <vector>
#include <map>
#include <string>

#include "Drawable.h"
#include "Rule.h"
#include "raylib.h"

class Loop : public virtual Drawable {

    int gridLength;
    int* grid;
    int* tempGrid;

    std::map<int, std::vector<Rule>> rules;
    NeighborhoodType ruleType;

    int cellWidth{ 0 };
    std::vector<Color> stateColors;

    void parseInitialStateData( const char* iniStateData, int xOffset, int yOffset );
    void parseRuleData( const char* ruleData );
    void processVonNeumannRule( int line, int column );
    void processMooreRule( int line, int column );

public:
    Loop( 
        int gridLength, 
        std::string initialStateFilePath, 
        std::string ruleDataFilePath, 
        NeighborhoodType ruleType,
        std::vector<Color> stateColors,
        int xOffset, 
        int yOffset );
    virtual ~Loop();
    void draw() override;
    void updateCellWidth( int screenWidth );
    void next();

};
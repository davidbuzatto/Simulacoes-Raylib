/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    *gw = (GameWorld){0};
    gw->gridLines = GRID_LINES;
    gw->gridColumns = GRID_COLUMNS;
    gw->celllWidth = 4;

    gw->colors[0] = BLACK;
    gw->colors[1] = BLUE;
    gw->colors[2] = RED;
    gw->colors[3] = GREEN;
    gw->colors[4] = YELLOW;
    gw->colors[5] = MAGENTA;
    gw->colors[6] = WHITE;
    gw->colors[7] = (Color){ 0, 255, 255, 255 };

    gw->timeToNextState = .01;

    const char *iniData = LoadFileText( "LangtonLoopInitialState.txt" );

    int line = 0;
    int column = 0;
    int lineOffset = gw->gridLines / 2 - 10;
    int columnOffset = gw->gridColumns / 2 - 10;
    while ( *iniData != '\0' ) {
        if ( *iniData == '\n' ) {
            line++;
            column = 0;
        } else {
            gw->grid[line+lineOffset][(column++)+columnOffset] = (int) (*iniData - 48);

        }
        iniData++;
    }

    const char *ruleData = LoadFileText( "LangtonLoopRules.txt" );

    line = 0;
    column = 0;
    while ( *ruleData != '\0' ) {
        if ( *ruleData == '\n' ) {
            line++;
            column = 0;
        } else {
            gw->rules[line][column++] = (int) (*ruleData - 48);
        }
        ruleData++;
    }

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();
    gw->frameCounter += delta;
    if ( gw->frameCounter >= gw->timeToNextState ) {
        gw->frameCounter = 0;
        nextState( gw );
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    for ( int i = 0; i < gw->gridLines; i++ ) {
        for ( int j = 0; j < gw->gridColumns; j++ ) {
            DrawRectangle( j * gw->celllWidth, i * gw->celllWidth, gw->celllWidth, gw->celllWidth, gw->colors[gw->grid[i][j]] );
        }
    }

    /*for ( int i = 0; i <= gw->gridLines; i++ ) {
        DrawLine( 0, i * gw->celllWidth, GetScreenWidth(), i * gw->celllWidth, GRAY );
    }

    for ( int i = 0; i <= gw->gridColumns; i++ ) {
        DrawLine( i * gw->celllWidth, 0, i * gw->celllWidth, GetScreenHeight(), GRAY );
    }*/

    EndDrawing();

}

void nextState( GameWorld *gw ) {

    for ( int i = 0; i < gw->gridLines; i++ ) {
        for ( int j = 0; j < gw->gridColumns; j++ ) {

            int state = gw->grid[i][j];

            int n = i-1;
            if ( n < 0 ) {
                n = gw->gridLines + n;
            }
            int e = (j+1)%gw->gridColumns;
            int s = (i+1)%gw->gridLines;
            int w = j-1;
            if ( w < 0 ) {
                w = gw->gridColumns + w;
            }

            int d1 = gw->grid[n][j];
            int d2 = gw->grid[i][e];
            int d3 = gw->grid[s][j];
            int d4 = gw->grid[i][w];


            // each rule encodes 4 rules (rotate it 90 degrees)
            for ( int k = 0; k < 219; k++ ) {
                if ( gw->rules[k][0] == state ) {
                    if ( gw->rules[k][1] == d1 &&
                         gw->rules[k][2] == d2 &&
                         gw->rules[k][3] == d3 &&
                         gw->rules[k][4] == d4 ) {
                        gw->temp[i][j] = gw->rules[k][5];
                    } else if ( gw->rules[k][1] == d4 &&
                                gw->rules[k][2] == d1 &&
                                gw->rules[k][3] == d2 &&
                                gw->rules[k][4] == d3 ) {
                        gw->temp[i][j] = gw->rules[k][5];
                    } else if ( gw->rules[k][1] == d3 &&
                                gw->rules[k][2] == d4 &&
                                gw->rules[k][3] == d1 &&
                                gw->rules[k][4] == d2 ) {
                        gw->temp[i][j] = gw->rules[k][5];
                    } else if ( gw->rules[k][1] == d2 &&
                                gw->rules[k][2] == d3 &&
                                gw->rules[k][3] == d4 &&
                                gw->rules[k][4] == d1 ) {
                        gw->temp[i][j] = gw->rules[k][5];
                    }
                }
            }

        }
    }

    /*for ( int i = 0; i < gw->gridLines; i++ ) {
        for ( int j = 0; j < gw->gridColumns; j++ ) {
            gw->grid[i][j] = gw->temp[i][j];
        }
    }*/

    memcpy( gw->grid, gw->temp, gw->gridLines * gw->gridColumns * sizeof( gw->grid[0][0] ) );

}
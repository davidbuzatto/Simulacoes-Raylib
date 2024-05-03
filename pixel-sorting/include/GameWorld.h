/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"

typedef struct SortState {
    int i;
    int j;
} SortState;

typedef struct GameWorld {

    Color *pixels;
    int width;
    int height;

    int currentSortingLine;
    int currentSortingColumn;
    SortState sortState;

} GameWorld;



/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void lineSort( GameWorld *gw, int line, int (*comparator)( Color *c1, Color *c2 ) );
void lineSortStepByStep( GameWorld *gw, int line, SortState *sortState, int (*comparator)( Color *c1, Color *c2 ) );
void columnSort( GameWorld *gw, int column, int (*comparator)( Color *c1, Color *c2 ) );

int colorCompareRGB( Color *c1, Color *c2 );
int colorCompareHue( Color *c1, Color *c2 );
int colorCompareSaturation( Color *c1, Color *c2 );
int colorCompareValue( Color *c1, Color *c2 );
int colorCompareInteger( Color *c1, Color *c2 ); // same as RGB :D
int colorCompareDistance( Color *c1, Color *c2 );
float colorDistance( Color *c1, Color *c2 );
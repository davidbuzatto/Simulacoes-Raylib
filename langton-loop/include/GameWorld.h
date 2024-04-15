/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"

/*typedef struct Rule {
    int 
} Rule;*/

#define GRID_LINES 320 
#define GRID_COLUMNS 320

typedef struct GameWorld {

    int gridLines;
    int gridColumns;
    int grid[GRID_LINES][GRID_COLUMNS];
    int temp[GRID_LINES][GRID_COLUMNS];
    int celllWidth;
    Color colors[8];
    int rules[219][6];

    float frameCounter;
    float timeToNextState;


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

void nextState( GameWorld *gw );
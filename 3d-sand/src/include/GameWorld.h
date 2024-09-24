/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <stdbool.h>
#include "raylib/raylib.h"

typedef struct GameWorld {
    
    int depth;
    int lines;
    int columns;
    unsigned int *cells;

    float cellDim;
    float nextStepCounter;
    float timeToNextStep;

    Camera3D camera;

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

unsigned int getCellValue( GameWorld *gw, int k, int i, int j );
void setCellValue( GameWorld *gw, int k, int i, int j, unsigned int value );
void drawCell( int k, int i, int j, float dim, unsigned int hexColor );
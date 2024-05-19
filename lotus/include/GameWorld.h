/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "raylib.h"

typedef struct GameWorld {
    Vector2 pos;
    int lotusQuantity;
    float angleIncrement;
    float startDistance;
    float distanceIncrement;
    int petals;
    float petalWidth;
    float petalStretch;
    float petalJoin;
    float petalCurve;
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

void reset( GameWorld *gw );
float lotus( float angle, float multiplier );
float lotusParam( float angle, float multiplier, int petals, float petalWidth, float petalStretch, float petalJoin, float petalCurve );
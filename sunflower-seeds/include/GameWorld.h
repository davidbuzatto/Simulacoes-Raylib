/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Seed.h"

typedef struct GameWorld {
    
    int seedQuantity;
    int maxSeeds;
    float newSeedAngleIncrement;
    Seed *seeds;

    float timeToCreateNewSeed;
    float newSeedTimeAccumulator;

    float newSeedSpeed;
    float newMinSeedRadius;
    float newMaxSeedRadius;
    float maxDistanceToGrow;
    float maxDistanceToChangeColor;

    Color newSeedColor;

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

void createNewSeed( 
    GameWorld *gw, 
    float seedSpeed, 
    float minSeedRadius, 
    float maxSeedRadius, 
    float maxDistanceToGrow,
    float maxDistanceToChangeColor,
    Color seedColor );
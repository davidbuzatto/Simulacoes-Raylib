/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#define MAX_SEEDS 2000
#define NEW_SEED_ANGLE_INCREMENT 137.5f
#define TIME_TO_CREATE_NEW_SEED 0.05f
#define NEW_SEED_SPEED 10.0f
#define NEW_MIN_SEED_RADIUS 3.0f
#define NEW_MAX_SEED_RADIUS 18.0f
#define MAX_DISTANCE_TO_GROW GetScreenWidth() / 2
#define MAX_DISTANCE_TO_CHANGE_COLOR 200
#define NEW_SEED_COLOR WHITE

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->seedQuantity = 0;
    gw->maxSeeds = MAX_SEEDS;
    gw->newSeedAngleIncrement = NEW_SEED_ANGLE_INCREMENT;
    gw->seeds = (Seed*) malloc( gw->maxSeeds * sizeof(Seed) );

    gw->timeToCreateNewSeed = TIME_TO_CREATE_NEW_SEED;
    gw->newSeedTimeAccumulator = 0.0f;

    gw->newSeedSpeed = NEW_SEED_SPEED;
    gw->newMinSeedRadius = NEW_MIN_SEED_RADIUS;
    gw->newMaxSeedRadius = NEW_MAX_SEED_RADIUS;
    gw->maxDistanceToGrow = MAX_DISTANCE_TO_GROW,
    gw->maxDistanceToChangeColor = MAX_DISTANCE_TO_CHANGE_COLOR,
    gw->newSeedColor = NEW_SEED_COLOR;

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

    if ( gw->seedQuantity < gw->maxSeeds ) {

        gw->newSeedTimeAccumulator += GetFrameTime();
        if ( gw->newSeedTimeAccumulator > gw->timeToCreateNewSeed ) {
            gw->newSeedTimeAccumulator = 0.0f;
            createNewSeed( 
                gw, 
                gw->newSeedSpeed, 
                gw->newMinSeedRadius, 
                gw->newMaxSeedRadius, 
                gw->maxDistanceToGrow, 
                gw->maxDistanceToChangeColor, 
                gw->newSeedColor );
        }

        for ( int i = 0; i < gw->seedQuantity; i++ ) {
            Seed *seed = &gw->seeds[i];
            int c1 = seed->pos.x - ( GetScreenWidth() / 2 );
            int c2 = seed->pos.y - ( GetScreenHeight() / 2 );
            updateSeed( seed, sqrtf( c1*c1 + c2*c2 ) );
        }

    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    for ( int i = 0; i < gw->seedQuantity; i++ ) {
        drawSeed( &gw->seeds[i] );
    }

    EndDrawing();

}

void createNewSeed( 
    GameWorld *gw, 
    float seedSpeed, 
    float minSeedRadius, 
    float maxSeedRadius, 
    float maxDistanceToGrow,
    float maxDistanceToChangeColor,
    Color seedColor ) {

    gw->seeds[gw->seedQuantity] = (Seed){
        .pos = {
            GetScreenWidth() / 2,
            GetScreenHeight() / 2
        },
        .speed = seedSpeed,
        .angle = gw->newSeedAngleIncrement * gw->seedQuantity,
        .radius = minSeedRadius,
        .minRadius = minSeedRadius,
        .maxRadius = maxSeedRadius,
        .maxDistanceToGrow = maxDistanceToGrow,
        .maxDistanceToChangeColor = maxDistanceToChangeColor,
        .color = seedColor
    };

    gw->seedQuantity++;

}
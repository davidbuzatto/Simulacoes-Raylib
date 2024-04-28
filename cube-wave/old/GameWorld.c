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
#include "Bar.h"

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

    gw->barStripsQuantity = 25;
    gw->barStrips = (BarStrip*) malloc( gw->barStripsQuantity * sizeof( BarStrip ) );

    int q[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int yOffset = 0;

    for ( int i = 0; i < gw->barStripsQuantity; i++ ) {
        createBarStrip(
            &gw->barStrips[i],
            GetScreenWidth() / 2,
            GetScreenHeight() / 2 - 100 + yOffset,
            q[i],
            32,
            70,
            200,
            18,
            3,
            BLUE,
            ( gw->barStripsQuantity / 2 - q[i] ) * 10
        );
        yOffset += 9;
    }

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    for ( int i = 0; i < gw->barStripsQuantity; i++ ) {
        destroyBarsFromBarStrip( &gw->barStrips[i] );
    }
    free( gw->barStrips );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {
    for ( int i = 0; i < gw->barStripsQuantity; i++ ) {
        updateBarStrip( &gw->barStrips[i] );
    }
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    for ( int i = 0; i < gw->barStripsQuantity; i++ ) {
        drawBarStrip( &gw->barStrips[i] );
    }

    EndDrawing();

}
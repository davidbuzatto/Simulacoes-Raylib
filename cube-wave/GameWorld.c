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

    gw->barQuantity = 13;
    gw->bars = (Bar*) malloc( gw->barQuantity * sizeof( Bar ) );

    Bar *bars = gw->bars;

    int xc = GetScreenWidth() / 2;
    int yc = GetScreenHeight() / 2;
    int width = 32;
    int minHeight = 70;
    int maxHeight = 200;
    int topDiagonalHeight = 18;
    float angleStep = 3;
    Color color = GREEN;

    int q = gw->barQuantity / 2 + 1;
    int k = 0;

    for ( int i = 0; i < q; i++ ) {
        if ( i == 0 ) {
            bars[k++] = (Bar){
                .x = xc,
                .y = yc,
                .width = width,
                .minHeight = minHeight,
                .maxHeight = maxHeight,
                .topDiagonalHeight = topDiagonalHeight,
                .percent = (float) k / gw->barQuantity,
                .angle = (float) k / gw->barQuantity * 360,
                .angleStep = angleStep,
                .color = color
            };
        } else {
            int base = k+1;
            bars[k++] = (Bar){
                .x = xc - i * width,
                .y = yc,
                .width = width,
                .minHeight = minHeight,
                .maxHeight = maxHeight,
                .topDiagonalHeight = topDiagonalHeight,
                .percent = (float) k / gw->barQuantity,
                .angle = (float) base / gw->barQuantity * 360,
                .angleStep = angleStep,
                .color = color
            };
            bars[k++] = (Bar){
                .x = xc + i * width,
                .y = yc,
                .width = width,
                .minHeight = minHeight,
                .maxHeight = maxHeight,
                .topDiagonalHeight = topDiagonalHeight,
                .percent = (float) k / gw->barQuantity,
                .angle = (float) base / gw->barQuantity * 360,
                .angleStep = angleStep,
                .color = color
            };
        }
    }

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw->bars );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    for ( int i = 0; i < gw->barQuantity; i++ ) {
        updateBar( &gw->bars[i] );
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    for ( int i = 0; i < gw->barQuantity; i++ ) {
        drawBar( &gw->bars[i] );
    }

    EndDrawing();

}
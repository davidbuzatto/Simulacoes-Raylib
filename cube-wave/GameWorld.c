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

    //gw->n = 37;
    gw->n = 121;
    gw->bars = (Bar*) malloc( gw->n * gw->n * sizeof( Bar ) );

    int width = 32;
    int topDiagonalHeight = 18;
    //int width = 8;
    //int topDiagonalHeight = 4;
    int yOffset = topDiagonalHeight / 2;
    int xc = GetScreenWidth() / 2 - (width * gw->n/2) + width / 2;
    //int yc = GetScreenHeight() / 2 - (yOffset * gw->n/10);
    int yc = GetScreenHeight() / 2;

    /*Color colors[3][3] = {
        { RED, ORANGE, YELLOW },
        { PURPLE, GREEN, VIOLET },
        { GRAY, MAGENTA, BLUE },
    };

    int offsets[3][3] = {
        { 0, -1, -2 },
        { 1,  0, -1 },
        { 2,  1,  0 },
    };

    // squared
    int starts[3][3] = {
        { 2, 1, 2 },
        { 1, 0, 1 },
        { 2, 1, 2 },
    };*/

    int globalStart = gw->n - 1;
    int globalStartStep = -1;
    int mid = gw->n / 2;
    
    for ( int i = 0; i < gw->n; i++ ) {

        int offset = i;
        int localStart = globalStart;
        int localStartStep = -1;

        for ( int j = 0; j < gw->n; j++ ) {
            
            // circle
            float dist = hypotf( mid - i, mid - j );

            gw->bars[i*gw->n+j] = (Bar){
                .x = xc + j * width + ( width/2 * offset ),
                .y = yc + offset * yOffset,
                .width = width,
                //.minHeight = 30,
                .minHeight = 50,
                //.maxHeight = 100,
                .maxHeight = 200,
                .topDiagonalHeight = topDiagonalHeight,
                .percent = 0,
                //.angle = localStart * 15,
                .angle = dist * 30,
                //.angle = dist * 10,
                .angleStep = 3,
                .color = BLUE
            };

            offset--;
            localStart += localStartStep;
            if ( j == gw->n / 2 - 1 ) {
                localStartStep = 1;
            }

        }

        globalStart += globalStartStep;
        if ( i == gw->n / 2 - 1 ) {
            globalStartStep = 1;
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

    for ( int i = 0; i < gw->n; i++ ) {
        for ( int j = 0; j < gw->n; j++ ) {
            updateBar( &gw->bars[i*gw->n+j] );
        }
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );
    
    // infers level by level drawing order from top right corner to bottom left corner

    int quantity = 1;
    int inc = 1;
    int max = gw->n * 2 - 1;
    int iOffset = 0;

    for ( int levels = 0; levels < max; levels++ ) {

        int iStart = 0 + iOffset;
        int jStart = gw->n - levels - 1;
        if ( jStart < 0 ) {
            jStart = 0;
        }

        for ( int k = 0; k < quantity; k++ ) {
            int i = iStart+k;
            int j = jStart+k;
            drawBar( &gw->bars[i*gw->n+j] );
        }

        quantity += inc;
        if ( levels >= gw->n-2 ) {
            inc = -1;
        }
        if ( levels > gw->n-2 ) {
            iOffset++;
        }

    }

    EndDrawing();

}
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
#include "utils.h"

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

    //Image sourceImg = LoadImage( "resources/images/ff7-logo.png" );
    Image sourceImg = LoadImage( "resources/images/winXP.png" );
    circlePacking( gw, &sourceImg, 5, 30 );
    UnloadImage( sourceImg );

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

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    for ( int i = 0; i < gw->circleQuantity; i++ ) {
        Circle *c = &gw->circles[i];
        DrawCircle( c->pos.x, c->pos.y, c->radius, c->color );
        //DrawCircleLines( c->pos.x, c->pos.y, c->radius, c->color );
    }

    EndDrawing();

}

void circlePacking( GameWorld *gw, Image *src, int minRadius, int maxRadius ) {

    /*int lines = ( src->height / ( minRadius * 2 ) + 1 );
    int columns = ( src->width / ( minRadius * 2 ) + 1 );*/
    int lines = 40;
    int columns = 50;

    gw->circleQuantity = 0;
    gw->circleCapacity = lines * columns;
    gw->circles = (Circle*) malloc( sizeof( Circle ) * gw->circleCapacity );

    int iterations = 300;
    int p = 0;

    for ( int y = 0; y < lines; y++ ) {
        for ( int x = 0; x < columns; x++ ) {
            int radius = GetRandomValue( minRadius, maxRadius );
            gw->circles[p++] = (Circle){
                .pos = {
                    .x = x * radius,
                    .y = y * radius
                },
                .radius = radius,
                .color = BLACK
            };
        }
    }
    gw->circleQuantity = p;

    for ( int k = 0; k < iterations; k++ ) {
        for ( int i = 0; i < p; i++ ) {
            for ( int j = 0; j < p; j++ ) {
                if ( i != j ) {
                    Circle *c1 = &gw->circles[i];
                    Circle *c2 = &gw->circles[j];
                    float cat1 = c2->pos.x - c1->pos.x;
                    float cat2 = c2->pos.y - c1->pos.y;
                    float dist = sqrtf( cat1 * cat1 + cat2 * cat2 );
                    float distMax = c1->radius + c2->radius;
                    if ( dist < distMax ) {
                        float halfDif = (distMax - dist) / 2;
                        float ang = atan2f( cat2, cat1 );
                        float moveX = halfDif * cosf( ang );
                        float moveY = halfDif * sinf( ang );
                        c1->pos.x -= moveX;
                        c1->pos.y -= moveY;
                        c2->pos.x += moveX;
                        c2->pos.y += moveY;
                    }
                }
            }
        }
    }

    for ( int i = 0; i < gw->circleQuantity; i++ ) {
        Circle *c = &gw->circles[i];
        if ( c->pos.x >= 0 && c->pos.x < src->width &&
             c->pos.y >= 0 && c->pos.y < src->height ) {
            Color pColor = GetImageColor( *src, c->pos.x, c->pos.y );
            c->color = pColor;
        } else {
            c->color = (Color){ .r = 0, .g = 0, .b = 0, .a = 0 };
        }
    }

}
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
#include <string.h>
#include <assert.h>

#include "GameWorld.h"
#include "ResourceManager.h"

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
    gw->level = 1;
    gw->maxLevel = 10;

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

    if ( IsKeyPressed( KEY_UP ) ) {
        gw->level++;
        if ( gw->level > gw->maxLevel ) {
            gw->level = gw->maxLevel;
        }
    } else if ( IsKeyPressed( KEY_DOWN ) ) {
        gw->level--;
        if ( gw->level < 1 ) {
            gw->level = 1;
        }
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    float angle = 90;
    float currentAngle = 180;
    int level = gw->level;
    float size = GetScreenWidth() / pow( 2, level );
    Vector2 startPos = { GetScreenWidth() - size / 2, GetScreenHeight() - size / 2 };

    hilbertCurve( &startPos, level, size, angle, &currentAngle );

    EndDrawing();

}

int getDimensionFromGeneration( int generation ) {
    return (int) sqrt( (int) pow( 4, generation ) );
}

void hilbertCurve( Vector2 *currentPos, int level, float size, float angle, float *currentAngle ) {

    if ( level == 0 ) {
        return;
    }

    *currentAngle += angle;
    hilbertCurve( currentPos, level-1, size, -angle, currentAngle );

    Vector2 newPos = { 
        currentPos->x + size * cosf( DEG2RAD * *currentAngle ),
        currentPos->y + size * sinf( DEG2RAD * *currentAngle )
    };
    DrawLineV( *currentPos, newPos, BLACK );
    *currentPos = newPos;
    *currentAngle -= angle;
    hilbertCurve( currentPos, level-1, size, angle, currentAngle );

    newPos.x = currentPos->x + size * cosf( DEG2RAD * *currentAngle );
    newPos.y = currentPos->y + size * sinf( DEG2RAD * *currentAngle );
    DrawLineV( *currentPos, newPos, BLACK );
    *currentPos = newPos;
    hilbertCurve( currentPos, level-1, size, angle, currentAngle );

    *currentAngle -= angle;
    newPos.x = currentPos->x + size * cosf( DEG2RAD * *currentAngle );
    newPos.y = currentPos->y + size * sinf( DEG2RAD * *currentAngle );
    DrawLineV( *currentPos, newPos, BLACK );
    *currentPos = newPos;
    hilbertCurve( currentPos, level-1, size, -angle, currentAngle );

    *currentAngle += angle;

}
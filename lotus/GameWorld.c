/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "include/GameWorld.h"
#include "include/ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "include/raygui.h"      // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->pos = (Vector2) {
        GetScreenWidth() / 2,
        GetScreenHeight() / 2
    };

    reset( gw );

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

    if ( IsKeyDown( KEY_R ) ) {
        reset( gw );
    }

    if ( IsKeyPressed( KEY_ONE ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->lotusQuantity--;
        } else {
            gw->lotusQuantity++;
        }
    }

    if ( IsKeyPressed( KEY_TWO ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->angleIncrement -= 0.2f;
        } else {
            gw->angleIncrement += 0.2f;
        }
    }

    if ( IsKeyDown( KEY_THREE ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->startDistance--;
        } else {
            gw->startDistance++;
        }
    }

    if ( IsKeyDown( KEY_FOUR ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->distanceIncrement--;
        } else {
            gw->distanceIncrement++;
        }
    }

    if ( IsKeyPressed( KEY_FIVE ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->petals -= 2;
        } else {
            gw->petals += 2;
        }
    }

    if ( IsKeyDown( KEY_SIX ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->petalWidth -= 0.25f;
        } else {
            gw->petalWidth += 0.25f;
        }
    }

    if ( IsKeyDown( KEY_SEVEN ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->petalStretch -= 0.25f;
        } else {
            gw->petalStretch += 0.25f;
        }
    }

    if ( IsKeyDown( KEY_EIGHT ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->petalJoin -= 0.25f;
        } else {
            gw->petalJoin += 0.25f;
        }
    }

    if ( IsKeyDown( KEY_NINE ) ) {
        if ( IsKeyDown( KEY_LEFT_SHIFT ) ) {
            gw->petalCurve -= 0.25f;
        } else {
            gw->petalCurve += 0.25f;
        }
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground(WHITE);

    for ( int i = 0; i < gw->lotusQuantity; i++ ) {

        float currentAngle = 0.0f;
        float multiplier = gw->startDistance + gw->distanceIncrement * i;
        Vector2 currentPoint;
        Vector2 firstPoint;
        Vector2 lastPoint;
        bool first = true;

        while ( currentAngle < 360.0f ) {

            //float d = lotus(DEG2RAD * currentAngle, multiplier);
            float d = lotusParam(DEG2RAD * currentAngle, multiplier, gw->petals, gw->petalWidth, gw->petalStretch, gw->petalJoin, gw->petalCurve );
            currentPoint.x = gw->pos.x + d * cosf(DEG2RAD * currentAngle);
            currentPoint.y = gw->pos.y + d * sinf(DEG2RAD * currentAngle);

            if ( first ) {
                firstPoint = currentPoint;
                first = false;
            } else {
                DrawLineV( lastPoint, currentPoint, BLACK );
            }

            lastPoint = currentPoint;
            currentAngle += gw->angleIncrement;

        }

        DrawLineV( lastPoint, firstPoint, BLACK );

    }

    EndDrawing();

}

void reset( GameWorld *gw ) {
    gw->lotusQuantity = 5;
    gw->angleIncrement = 0.2f;
    gw->startDistance = 50.0f;
    gw->distanceIncrement = 50.0f;
    gw->petals = 6;
    gw->petalWidth = 1;
    gw->petalStretch = 2;
    gw->petalJoin = 0.25f;
    gw->petalCurve = 8;
}

float lotus( float angle, float multiplier ) {
    float num = (float) ( fabs( cosf( 3 * angle ) ) + 2 * ( 0.25f - fabs( cosf( 3 * angle + PI / 2 ) ) ) );
    float den = (float) ( 2 + 8 * fabs( cosf( 6 * angle + PI / 2 ) ) );
    return ( 1 + num / den ) * multiplier;
}

float lotusParam( float angle, float multiplier, int petals, float petalWidth, float petalStretch, float petalJoin, float petalCurve ) {
    float num = (float) ( fabs( cosf( petals / 2 * angle ) ) + 2 * ( petalJoin - fabs( cosf( petals / 2 * angle + PI / 2 ) ) ) );
    float den = (float) ( petalStretch + petalCurve * fabs( cosf( petals * angle + PI / 2 ) ) );
    return ( petalWidth + num / den ) * multiplier;
}

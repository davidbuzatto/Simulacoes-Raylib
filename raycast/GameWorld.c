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

#include "LightSource.h"
#include "LightBeam.h"
#include "Obstacle.h"
#include "utils.h"

#define MAX_OBSTACLES 20

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    gw->ls = createLightSource( 360, YELLOW, 0, MAX_OBSTACLES );
    gw->obstacleQuantity = MAX_OBSTACLES;
    gw->obstacles = (Obstacle*) malloc( gw->obstacleQuantity * sizeof( Obstacle ) );

    /*gw->obstacles[0] = (Obstacle){ { 600, 100 }, { 600, 700 }, .color = WHITE };
    gw->obstacles[1] = (Obstacle){ { 200, 100 }, { 200, 700 }, .color = WHITE };
    gw->obstacles[2] = (Obstacle){ { 100, 300 }, { 300, 100 }, .color = WHITE };
    gw->obstacles[3] = (Obstacle){ { 300, 600 }, { 500, 600 }, .color = WHITE };
    gw->obstacles[4] = (Obstacle){ { 700, 700 }, { 700, 100 }, .color = WHITE };
    gw->obstacles[5] = (Obstacle){ { 300, 200 }, { 500, 200 }, .color = WHITE };

    gw->obstacles[6] = (Obstacle){ {  50,  50 }, { 750,  50 }, .color = WHITE };
    gw->obstacles[7] = (Obstacle){ { 750,  50 }, { 750, 750 }, .color = WHITE };
    gw->obstacles[8] = (Obstacle){ { 750, 750 }, {  50, 750 }, .color = WHITE };
    gw->obstacles[9] = (Obstacle){ {  50, 750 }, {  50,  50 }, .color = WHITE };*/

    gw->obstacles[0] = (Obstacle){ { 0, 0 }, { w, 0 }, .color = WHITE };
    gw->obstacles[1] = (Obstacle){ { w, 0 }, { w, h }, .color = WHITE };
    gw->obstacles[2] = (Obstacle){ { w, h }, { 0, h }, .color = WHITE };
    gw->obstacles[3] = (Obstacle){ { 0, h }, { 0, 0 }, .color = WHITE };

    for ( int i = 4; i < gw->obstacleQuantity; i++ ) {
        gw->obstacles[i] = (Obstacle){ 
            { GetRandomValue( 0, w ), GetRandomValue( 0, w ) }, 
            { GetRandomValue( 0, h ), GetRandomValue( 0, h ) },
            .color = WHITE
        };
    }

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    destroyLightSource( gw->ls );
    free( gw->obstacles );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    LightSource *ls = gw->ls;
    Vector2 *collidedPoints = ls->collidedPoints;

    updateLightSource( ls );

    for ( int i = 0; i < ls->lightBeamQuantity; i++ ) {
        LightBeam *lb = &ls->lightBeams[i];
        int qc = 0;
        for ( int j = 0; j < gw->obstacleQuantity; j++ ) {
            Obstacle *ob = &gw->obstacles[j];
            Vector2 ip;
            //if ( getIntersectionPoint( lb, ob, &ip ) && containsPoint( ob, &ip ) ) {
            if ( getIntersectionPoint( lb, ob, &ip ) ) {
                //DrawCircleV( ip, 10, Fade( lb->color, 0.5 ) );
                collidedPoints[qc++] = ip;
            }
        }
        if ( qc != 0 ) {
            
            // insertion sort
            for ( int m = 1; m < qc; m++ ) {
                for ( int n = m; n > 0; n-- ) {
                    float ca1 = collidedPoints[n].x - ls->pos.x;
                    float ca2 = collidedPoints[n].y - ls->pos.y;
                    float da = ca1*ca1 + ca2*ca2;
                    float cb1 = collidedPoints[n-1].x - ls->pos.x;
                    float cb2 = collidedPoints[n-1].y - ls->pos.y;
                    float db = cb1*cb1 + cb2*cb2;
                    if ( db > da ) {
                        Vector2 temp = collidedPoints[n];
                        collidedPoints[n] = collidedPoints[n-1];
                        collidedPoints[n-1] = temp;
                    } else {
                        break;
                    }
                }
            }

            //DrawCircleV( collidedPoints[0], 10, lb->color );
            lb->endDraw = collidedPoints[0];

        } else {
            lb->endDraw = ls->pos;
        }

    }

    /*for ( int i = 0; i < gw->obstacleQuantity; i++ ) {
        Obstacle *ob = &gw->obstacles[i];
        int qc = 0;
        for ( int j = 0; j < ls->lightBeamQuantity; j++ ) {
            LightBeam *lb = &ls->lightBeams[j];
            Vector2 ip;
            if ( getIntersectionPoint( lb, ob, &ip ) && containsPoint( ob, &ip ) ) {
                DrawCircleV( ip, 10, lb->color );
                collidedPoints[qc++] = ip;
            }
        }
    }*/

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    drawLightSource( gw->ls );

    for ( int i = 0; i < gw->obstacleQuantity; i++ ) {
        drawObstacle( &gw->obstacles[i] );
    }

    EndDrawing();

}
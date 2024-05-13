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

    gw->generation = 0;

    int dimension = getDimensionFromGeneration( gw->generation );
    gw->current = (char*) malloc( dimension * dimension * sizeof( char ) );
    gw->current[0] = 'A';

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

        gw->generation++;

        if ( gw->generation > 8 ) {
            gw->generation = 8;
        } else {

            int currentDimension = getDimensionFromGeneration( gw->generation-1 );
            int dimension = getDimensionFromGeneration( gw->generation );
            size_t size = dimension * dimension * sizeof( char );

            gw->next = (char*) malloc( size );

            // process current generation
            for ( int i = 0; i < currentDimension; i++ ) {
                for ( int j = 0; j < currentDimension; j++ ) {

                    int iBase = i*2;
                    int jBase = j*2;

                    int iUpLeft = iBase;
                    int jUpLeft = jBase;

                    int iUpRight = iBase;
                    int jUpRight = jBase+1;

                    int iDownLeft = iBase+1;
                    int jDownLeft = jBase;

                    int iDownRight = iBase+1;
                    int jDownRight = jBase+1;

                    switch ( gw->current[i*currentDimension+j] ) {
                        case 'A':
                            gw->next[iUpLeft*dimension+jUpLeft] = 'A';
                            gw->next[iUpRight*dimension+jUpRight] = 'A';
                            gw->next[iDownLeft*dimension+jDownLeft] = 'D';
                            gw->next[iDownRight*dimension+jDownRight] = 'B';
                            break;
                        case 'B':
                            gw->next[iUpLeft*dimension+jUpLeft] = 'B';
                            gw->next[iUpRight*dimension+jUpRight] = 'C';
                            gw->next[iDownLeft*dimension+jDownLeft] = 'B';
                            gw->next[iDownRight*dimension+jDownRight] = 'A';
                            break;
                        case 'C':
                            gw->next[iUpLeft*dimension+jUpLeft] = 'D';
                            gw->next[iUpRight*dimension+jUpRight] = 'B';
                            gw->next[iDownLeft*dimension+jDownLeft] = 'C';
                            gw->next[iDownRight*dimension+jDownRight] = 'C';
                            break;
                        case 'D':
                            gw->next[iUpLeft*dimension+jUpLeft] = 'C';
                            gw->next[iUpRight*dimension+jUpRight] = 'D';
                            gw->next[iDownLeft*dimension+jDownLeft] = 'A';
                            gw->next[iDownRight*dimension+jDownRight] = 'D';
                            break;
                        default:
                            assert( false );
                            break;
                    }

                }
            }


            free( gw->current );
            gw->current = (char*) malloc( size );
            memcpy( gw->current, gw->next, size );
            free( gw->next );

        }

    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    int dimension = getDimensionFromGeneration( gw->generation );
    float size = (float) GetScreenWidth() / dimension;
    float size2 = (float) GetScreenWidth() / (dimension * 2);
    float halfSize2 = size2 / 2;

    /*DrawText( TextFormat( "generation: %d", gw->generation ), 20, 20, 20, BLACK );
    DrawText( TextFormat( " dimension: %d", dimension ), 20, 40, 20, BLACK );

    for ( int i = 0; i < dimension*2; i++ ) {
        DrawLine( 0, size2*i, GetScreenWidth(), size2*i, BLACK );
        DrawLine( size2*i, 0, size2*i, GetScreenHeight(), BLACK );
    }*/

    for ( int i = 0; i < dimension; i++ ) {
        for ( int j = 0; j < dimension; j++ ) {

            float xc = size2 + j * size;
            float yc = size2 + i * size;
            char c = gw->current[i*dimension+j];

            /*DrawText( 
                TextFormat( "%c", c ), 
                xc, 
                yc, 
                20, BLACK );*/
            
            Vector2 vUpLeft = { xc - halfSize2, yc - halfSize2 };     // up left
            Vector2 vUpRight = { xc + halfSize2, yc - halfSize2 };    // up right
            Vector2 vDownLeft = { xc - halfSize2, yc + halfSize2 };   // down left
            Vector2 vDownRight = { xc + halfSize2, yc + halfSize2 };  // down right
            Vector2 vExtension1;
            Vector2 vExtension2;

            switch ( c ) {
                case 'A':
                    DrawLineV( vDownLeft, vUpLeft, BLACK );
                    DrawLineV( vUpLeft, vUpRight, BLACK );
                    DrawLineV( vUpRight, vDownRight, BLACK );
                    break;
                case 'B':
                    DrawLineV( vUpRight, vUpLeft, BLACK );
                    DrawLineV( vUpLeft, vDownLeft, BLACK );
                    DrawLineV( vDownLeft, vDownRight, BLACK );
                    break;
                case 'C':
                    DrawLineV( vUpRight, vDownRight, BLACK );
                    DrawLineV( vDownRight, vDownLeft, BLACK );
                    DrawLineV( vDownLeft, vUpLeft, BLACK );
                    break;
                case 'D':
                    DrawLineV( vDownLeft, vDownRight, BLACK );
                    DrawLineV( vDownRight, vUpRight, BLACK );
                    DrawLineV( vUpRight, vUpLeft, BLACK );
                    break;
                default:
                    assert( false );
                    break;
            }

        }
    }

    EndDrawing();

}

int getDimensionFromGeneration( int generation ) {
    return (int) sqrt( (int) pow( 4, generation ) );
}
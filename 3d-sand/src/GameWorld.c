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

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#define mapPosition( i, j, k ) (i) * gw->lines * gw->columns + (j) * gw->columns + (k);
unsigned int currentColor = 0xff9400ff;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->depth = 100;
    gw->lines = 50;
    gw->columns = 100;
    /*gw->depth = 10;
    gw->lines = 50;
    gw->columns = 10;*/
    gw->cells = (unsigned int*) calloc( gw->depth * gw->lines * gw->columns, sizeof( unsigned int ) );

    gw->cellDim = 0.1;

    gw->nextStepCounter = 0.0f;
    gw->timeToNextStep = 0.0f;

    gw->camera = (Camera3D) {
        .position = { gw->columns * gw->cellDim / 2, 4.0f, 19.0f },
        //.position = { gw->columns * gw->cellDim / 2, 1.0f, 7.0f },
        .target = { gw->columns * gw->cellDim / 2, gw->lines * gw->cellDim / 2, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    /*for ( int i = 0; i < gw->depth; i++ ) {
        for ( int j = 0; j < gw->lines; j++ ) {
            for ( int k = 0; k < gw->columns; k++ ) {
                setCellValue( gw, i, j, k, 0xff9400ff );
            }
        }
    }*/

    //setCellValue( gw, gw->depth / 2, gw->columns - 1, gw->columns / 2, 0xff9400ff );

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

    if ( IsKeyDown( KEY_UP ) ) {
        gw->camera.position.y += 0.1f;
    } else if ( IsKeyDown( KEY_DOWN ) ) {
        gw->camera.position.y -= 0.1f;
    } else if ( IsKeyDown( KEY_LEFT ) ) {
        gw->camera.position.x -= 0.1f;
    } else if ( IsKeyDown( KEY_RIGHT ) ) {
        gw->camera.position.x += 0.1f;
    } else if ( IsKeyDown( KEY_PAGE_UP ) ) {
        gw->camera.position.z -= 0.1f;
    } else if ( IsKeyDown( KEY_PAGE_DOWN ) ) {
        gw->camera.position.z += 0.1f;
    }

    if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        currentColor = ColorToInt( ColorFromHSV( GetRandomValue( 0, 360 ), 1.0f, 1.0f ) );
    }

    if ( IsMouseButtonDown( MOUSE_BUTTON_LEFT ) ) {
        for ( int i = 0; i < 100; i++ ) {

            int x = GetMouseX() / ( GetScreenWidth() / gw->columns );
            int y = GetMouseY() / ( GetScreenHeight() / gw->depth );

            int rColumn = GetRandomValue( 0, gw->columns / 10 - 1 );
            int rDepth = GetRandomValue( 0, gw->depth / 10 - 1 );
            
            x += GetRandomValue( 0, 1 ) == 0 ? rColumn : -rColumn;
            y += GetRandomValue( 0, 1 ) == 0 ? rDepth : -rDepth;

            if ( x < 0 ) {
                x = 0;
            } else if ( x >= gw->columns ) {
                x = gw->columns - 1;
            }

            if ( y < 0 ) {
                y = 0;
            } else if ( y >= gw->depth ) {
                y = gw->depth - 1;
            }

            setCellValue( gw, y, gw->lines - 1, x, currentColor );
        }
    }

    gw->nextStepCounter += GetFrameTime();

    if ( gw->nextStepCounter >= gw->timeToNextStep ) {

        gw->nextStepCounter = 0.0f;

        for ( int i = 0; i < gw->depth; i++ ) {
            for ( int j = gw->lines-1; j >= 0; j-- ) {
                for ( int k = 0; k < gw->columns; k++ ) {

                    unsigned int v = getCellValue( gw, i, j, k );

                    if ( v ) {
                        
                        int lowerP = j-1;

                        if ( lowerP >= 0 ) {
                            unsigned int lowerN = getCellValue( gw, i, lowerP, k );
                            if ( !lowerN ) {
                                // baixo
                                setCellValue( gw, i, lowerP, k, v );
                                setCellValue( gw, i, j, k, 0 );
                            } else {

                                // vizinhança
                                int leftP = k-1;
                                int rightP = k+1;
                                int farP = i-1;
                                int nearP = i+1;

                                switch ( GetRandomValue( 0, 7 ) ) {
                                    case 0:
                                        if ( leftP >= 0 ) {
                                            unsigned int vv = getCellValue( gw, i, j, leftP );
                                            if ( !vv ) {
                                                setCellValue( gw, i, j, leftP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 1:
                                        if ( rightP < gw->columns ) {
                                            unsigned int vv = getCellValue( gw, i, j, rightP );
                                            if ( !vv ) {
                                                setCellValue( gw, i, j, rightP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 2:
                                        if ( farP >= 0 ) {
                                            unsigned int vv = getCellValue( gw, farP, j, k );
                                            if ( !vv ) {
                                                setCellValue( gw, farP, j, k, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 3:
                                        if ( nearP < gw->depth ) {
                                            unsigned int vv = getCellValue( gw, nearP, j, k );
                                            if ( !vv ) {
                                                setCellValue( gw, nearP, j, k, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 4:
                                        if ( leftP >= 0 && farP >= 0 ) {
                                            unsigned int vv = getCellValue( gw, farP, j, leftP );
                                            if ( !vv ) {
                                                setCellValue( gw, farP, j, leftP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 5:
                                        if ( leftP >= 0 && nearP < gw->depth ) {
                                            unsigned int vv = getCellValue( gw, nearP, j, leftP );
                                            if ( !vv ) {
                                                setCellValue( gw, nearP, j, leftP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 6:
                                        if ( rightP < gw->columns && farP >= 0 ) {
                                            unsigned int vv = getCellValue( gw, farP, j, rightP );
                                            if ( !vv ) {
                                                setCellValue( gw, farP, j, rightP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                    case 7:
                                        if ( rightP < gw->columns && nearP < gw->depth ) {
                                            unsigned int vv = getCellValue( gw, nearP, j, rightP );
                                            if ( !vv ) {
                                                setCellValue( gw, nearP, j, rightP, v );
                                                setCellValue( gw, i, j, k, 0 );
                                            }
                                        }
                                        break;

                                }

                            }
                        } else {
                            setCellValue( gw, i, j, k, v );
                        }

                    }

                }

            }

        }

    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    BeginMode3D( gw->camera );

    Vector3 basePosition = {
        gw->columns * gw->cellDim / 2 - gw->cellDim / 2,
        0.0f - gw->cellDim,
        gw->depth * gw->cellDim / 2 - gw->cellDim / 2
    };

    DrawCube( basePosition, gw->columns * gw->cellDim, 0.1f, gw->depth * gw->cellDim, BLUE );
    DrawCubeWires( basePosition, gw->columns * gw->cellDim, 0.1f, gw->depth * gw->cellDim, BLACK );

    for ( int i = 0; i < gw->depth; i++ ) {
        for ( int j = 0; j < gw->lines; j++ ) {
            for ( int k = 0; k < gw->columns; k++ ) {
                if ( getCellValue( gw, i, j, k ) ) {
                    drawCell( i, j, k, gw->cellDim, getCellValue( gw, i, j, k ) );
                }
            }
        }
    }

    EndMode3D();

    DrawText( TextFormat( "%.2f %.2f %.2f", gw->camera.position.x, gw->camera.position.y, gw->camera.position.z ), 10, 10, 20, BLACK );

    EndDrawing();

}

unsigned int getCellValue( GameWorld *gw, int i, int j, int k ) {
    int p = mapPosition( i, j, k );
    return gw->cells[p];
}

void setCellValue( GameWorld *gw, int i, int j, int k, unsigned int value ) {
    int p = mapPosition( i, j, k );
    gw->cells[p] = value;
}

void drawCell( int i, int j, int k, float dim, unsigned int hexColor ) {
    Vector3 pos = { k * dim, j * dim, i * dim };
    DrawCube( pos, dim, dim, dim, GetColor( hexColor ) );
    DrawCubeWires( pos, dim, dim, dim, BLACK );
}
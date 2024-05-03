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

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    *gw = (GameWorld){0};

    //Image img = LoadImage( "resources/images/tifa.png" );
    //Image img = LoadImage( "resources/images/t4.png" );
    Image img = LoadImage( "resources/images/t4a.png" );
    gw->pixels = (Color*) malloc( img.width * img.height * sizeof( Color ) );
    gw->width = img.width;
    gw->height = img.height;

    gw->sortState.i = 1;
    gw->sortState.j = gw->sortState.i;

    for ( int i = 0; i < img.height; i++ ) {
        for ( int j = 0; j < img.width; j++ ) {
            gw->pixels[i*img.width+j] = GetImageColor( img, j, i );
        }
    }

    UnloadImage( img );

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw->pixels );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    int (*comparator)( Color*, Color* ) = colorCompareValue;
    //int (*comparator)( Color*, Color* ) = colorCompareSaturation;
    //int (*comparator)( Color*, Color* ) = colorCompareHue;
    //int (*comparator)( Color*, Color* ) = colorCompareRGB;
    //int (*comparator)( Color*, Color* ) = colorCompareInteger;
    //int (*comparator)( Color*, Color* ) = colorCompareDistance;

    if ( gw->currentSortingLine < gw->height ) {
        for ( int i = 0; i < 1000; i++ ) {
            lineSortStepByStep( gw, gw->currentSortingLine, &gw->sortState, comparator );
        }
        if ( gw->sortState.i == gw->width ) {
            gw->currentSortingLine++;
            gw->sortState.i = 1;
            gw->sortState.j = gw->sortState.i;
        }
    }

    /*if ( gw->currentSortingLine < gw->height ) {
        lineSort( gw, gw->currentSortingLine, comparator );
        gw->currentSortingLine++;
    } else if ( gw->currentSortingColumn < gw->width ) {
        columnSort( gw, gw->currentSortingColumn, comparator );
        gw->currentSortingColumn++;
    }*/

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    int w = 5;

    for ( int i = 0; i < gw->height; i++ ) {
        for ( int j = 0; j < gw->width; j++ ) {
            //DrawPixel( j, i, gw->pixels[i*gw->width+j] );
            DrawRectangle( j*w, i*w, w, w, gw->pixels[i*gw->width+j] );
        }
    }

    /*for ( int i = 0; i < gw->height; i++ ) {
        DrawLine( 0, i*w, GetScreenWidth(), i*w, BLACK );
    }

    for ( int i = 0; i < gw->width; i++ ) {
        DrawLine( i*w, 0, i*w, GetScreenHeight(), BLACK );
    }*/

    EndDrawing();

}

void lineSort( GameWorld *gw, int line, int (*comparator)( Color *c1, Color *c2 ) ) {

    if ( line >= 0 && line < gw->height ) {

        // insertion sort
        for ( int i = 1; i < gw->width; i++ ) {
            for ( int j = i; j > 0; j-- ) {
                int p1 = line*gw->width+j;
                int p2 = p1-1;
                int comp = comparator( &gw->pixels[p1], &gw->pixels[p2] );
                if ( comp < 0 ) {
                    Color temp = gw->pixels[p1];
                    gw->pixels[p1] = gw->pixels[p2];
                    gw->pixels[p2] = temp;
                }
            }
        }

    }

}

void lineSortStepByStep( GameWorld *gw, int line, SortState *sortState, int (*comparator)( Color *c1, Color *c2 ) ) {

    if ( line >= 0 && line < gw->height ) {

        int i = sortState->i;
        int j = sortState->j;
        
        if ( i < gw->width ) {
            if ( j > 0 ) {
                int p1 = line*gw->width+j;
                int p2 = p1-1;
                int comp = comparator( &gw->pixels[p1], &gw->pixels[p2] );
                if ( comp < 0 ) {
                    Color temp = gw->pixels[p1];
                    gw->pixels[p1] = gw->pixels[p2];
                    gw->pixels[p2] = temp;
                }
                sortState->j--;
                if ( sortState->j == 0 ) {
                    sortState->i++;
                    sortState->j = sortState->i;
                }
            }
        }

    }

}

void columnSort( GameWorld *gw, int column, int (*comparator)( Color *c1, Color *c2 ) ) {

    if ( column >= 0 && column < gw->width ) {

        // insertion sort
        for ( int i = 1; i < gw->height; i++ ) {
            for ( int j = i; j > 0; j-- ) {
                int p1 = j*gw->width+column;
                int p2 = (j-1)*gw->width+column;
                int comp = comparator( &gw->pixels[p1], &gw->pixels[p2] );
                if ( comp < 0 ) {
                    Color temp = gw->pixels[p1];
                    gw->pixels[p1] = gw->pixels[p2];
                    gw->pixels[p2] = temp;
                }
            }
        }

    }

}

int colorCompareRGB( Color *c1, Color *c2 ) {
    
    // RGB
    if ( c1->r < c2->r ) {
        return -1;
    } else if ( c1->r > c2->r ) {
        return 1;
    } else if ( c1->g < c2->g ) {
        return -1;
    } else if ( c1->g > c2->g ) {
        return 1;
    } else if ( c1->b < c2->b ) {
        return -1;
    } else if ( c1->b > c2->b ) {
        return 1;
    }

    return 0;

}

int colorCompareHue( Color *c1, Color *c2 ) {

    // matiz (x), saturação (y) e brilho (z)
    Vector3 hsv1 = ColorToHSV( *c1 );
    Vector3 hsv2 = ColorToHSV( *c2 );

    if ( hsv1.x < hsv2.x ) {
        return -1;
    } else if ( hsv1.x > hsv2.x ) {
        return 1;
    }

    return 0;

}

int colorCompareSaturation( Color *c1, Color *c2 ) {

    Vector3 hsv1 = ColorToHSV( *c1 );
    Vector3 hsv2 = ColorToHSV( *c2 );

    if ( hsv1.y < hsv2.y ) {
        return -1;
    } else if ( hsv1.y > hsv2.y ) {
        return 1;
    }

    return 0;

}

int colorCompareValue( Color *c1, Color *c2 ) {

    Vector3 hsv1 = ColorToHSV( *c1 );
    Vector3 hsv2 = ColorToHSV( *c2 );

    if ( hsv1.z < hsv2.z ) {
        return -1;
    } else if ( hsv1.z > hsv2.z ) {
        return 1;
    }

    return 0;

}

int colorCompareInteger( Color *c1, Color *c2 ) {
    return ColorToInt( *c1 ) - ColorToInt( *c2 );
}

int colorCompareDistance( Color *c1, Color *c2 ) {

    int distance = (int) ( colorDistance( c1, c2 ) * 1000 );
    
    if ( distance == 0 ) {
        return 0;
    } else if ( distance > 1000 ) {
        return 1;
    }

    return -1;

}

float colorDistance( Color *c1, Color *c2 ) {
    float r = c2->r - c1->r;
    float g = c2->g - c1->g;
    float b = c2->b - c1->b;
    return sqrtf( r*r + g*g + b*b );
}
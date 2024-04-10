/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "BST.h"

#define TEST_RANDOM_DATA_SIZE 50
#define TEST_1_DATA_SIZE 7
#define TEST_2_DATA_SIZE 10
#define MARGIN_LEFT 10
#define MARGIN_TOP 10
#define RADIUS 10
#define SPACING 1
#define FONT_SIZE 10
#define DRAW_BST_FIRST false

float zoomLevel = 1;
Vector2 offset;
Vector2 mousePressPos;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    offset = (Vector2){0};

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->bst = newBST();
    gw->rbt = newRBT();

    gw->marginLeft = MARGIN_LEFT;
    gw->marginTop = MARGIN_TOP;
    gw->nodeRadius = RADIUS;
    gw->nodeSpacing = SPACING;
    gw->nodeFontSize = FONT_SIZE;
    gw->drawBstFirst = DRAW_BST_FIRST;
    gw->bstMaxLevel = 0;
    gw->rbtMaxBlackLevel = 0;

    int currentRank;
    int redNodeCount = 0;

    int test1Data[TEST_1_DATA_SIZE] = { 20, 10, 5, 15, 30, 25, 35 };

    int test2Data[TEST_2_DATA_SIZE] = { 
        (int) 'S', 
        (int) 'E', 
        (int) 'A', 
        (int) 'R', 
        (int) 'C', 
        (int) 'H', 
        (int) 'X', 
        (int) 'M', 
        (int) 'P', 
        (int) 'L'
    };
    
    int testRandomData[TEST_RANDOM_DATA_SIZE];
    for ( int i = 0; i < TEST_RANDOM_DATA_SIZE; i++ ) {
        testRandomData[i] = i+1;
    }
    for ( int i = 0; i < TEST_RANDOM_DATA_SIZE; i++ ) {
        int p = GetRandomValue( 0, TEST_RANDOM_DATA_SIZE-1 );
        int t = testRandomData[i];
        testRandomData[i] = testRandomData[p];
        testRandomData[p] = t;
    }

    for ( int i = 0; i < TEST_1_DATA_SIZE; i++ ) {
        bstPut( gw->bst, test1Data[i] );
        rbtPut( gw->rbt, test1Data[i] );
    }

    for ( int i = 0; i < TEST_2_DATA_SIZE; i++ ) {
        bstPut( gw->bst, test2Data[i] );
        rbtPut( gw->rbt, test2Data[i] );
    }

    for ( int i = 0; i < TEST_RANDOM_DATA_SIZE; i++ ) {
        bstPut( gw->bst, testRandomData[i] );
        rbtPut( gw->rbt, testRandomData[i] );
    }

    currentRank = 0;
    bstProcess( gw->bst->root, &currentRank, 0, &gw->bstMaxLevel );

    currentRank = 0;
    rbtProcess( gw->rbt->root, &currentRank, 0, &redNodeCount, &gw->rbtMaxBlackLevel );

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

    float mwm = GetMouseWheelMove();

    if ( mwm > 0 ) {
        zoomLevel *= 1.1;
        if ( zoomLevel > 10 ) {
            zoomLevel = 10;
        }
    } else if ( mwm < 0 ) {
        zoomLevel *= 0.9;
        if ( zoomLevel < 1 ) {
            zoomLevel = 1;
        }
    }

    gw->nodeRadius = (int) RADIUS * zoomLevel;
    gw->nodeSpacing = (int) SPACING * zoomLevel;
    gw->nodeFontSize = (int) FONT_SIZE * zoomLevel;

    if ( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) ) {
        mousePressPos = GetMousePosition();
    }

    if ( IsMouseButtonDown( MOUSE_LEFT_BUTTON ) ) {
        Vector2 mousePos = GetMousePosition();
        offset.x += mousePos.x - mousePressPos.x;
        offset.y += mousePos.y - mousePressPos.y;
        mousePressPos = mousePos;
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    if ( DRAW_BST_FIRST ) {
        bstDraw( gw->bst, 
                 gw->marginLeft + offset.x, gw->marginTop + offset.y, 
                 gw->nodeRadius, gw->nodeSpacing, gw->nodeFontSize );
        rbtDraw( gw->rbt, 
                 gw->marginLeft + offset.x, gw->marginTop * 2 + offset.y + (gw->bstMaxLevel+1) * (gw->nodeRadius * 2 + gw->nodeSpacing), 
                 gw->nodeRadius, gw->nodeSpacing, gw->nodeFontSize );
    } else {
        rbtDraw( gw->rbt, 
                 gw->marginLeft + offset.x, gw->marginTop + offset.y, 
                 gw->nodeRadius, gw->nodeSpacing, gw->nodeFontSize );
        bstDraw( gw->bst, 
                 gw->marginLeft + offset.x, gw->marginTop * 2 + offset.y + (gw->rbtMaxBlackLevel+2) * (gw->nodeRadius * 2 + gw->nodeSpacing), 
                 gw->nodeRadius, gw->nodeSpacing, gw->nodeFontSize );
    }

    EndDrawing();

}
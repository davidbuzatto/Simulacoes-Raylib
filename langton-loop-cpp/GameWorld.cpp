/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <iostream>
#include <string>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Construct a new GameWorld object
 */
GameWorld::GameWorld()
    :
    /*loop( // Langton loop
        200, 
        "resources/loopData/LangtonLoopInitialState.txt", 
        "resources/loopData/LangtonLoopRules.txt",
        NeighborhoodType::VON_NEUMANN, 
        { BLACK, BLUE, RED, GREEN, YELLOW, MAGENTA, WHITE, Color( 0, 255, 255, 255 ) },
        100, 
        100
    ),*/
    loop( // Byls loop
        50, 
        "resources/loopData/BylsLoopInitialState.txt", 
        "resources/loopData/BylsLoopRules.txt", 
        NeighborhoodType::VON_NEUMANN, 
        { BLACK, BLUE, RED, GREEN, YELLOW, MAGENTA },
        20, 
        20
    ),
    timeToNext( 2 ) {
};

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() = default;

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

    float delta = GetFrameTime();
    timeToNextAcum += delta;
    if ( timeToNextAcum >= timeToNext ) {
        timeToNextAcum = 0;
        loop.next();
    }

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() {

    BeginDrawing();
    ClearBackground( WHITE );

    loop.updateCellWidth( static_cast<int>( GetScreenWidth() ) );
    loop.draw();
    DrawFPS( 20, 20 );

    EndDrawing();

}

/**
 * @brief Load game resources like images, textures, sounds, fonts, shaders,
 * etc. It will be called in Game Window after the creation of the Raylib
 * window.
 */
void GameWorld::loadResources() {
    ResourceManager::loadResources();
}

/**
 * @brief Unload the once loaded game resources. It will be called
 * after the game loop ends.
 */
void GameWorld::unloadResources() {
    ResourceManager::unloadResources();
}
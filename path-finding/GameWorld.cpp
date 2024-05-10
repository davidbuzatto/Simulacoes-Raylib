/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <iostream>
#include <string>
#include <format>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib.h"
//#include "raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raygui.h"              // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "EdgeWeightedGraph.h"
#include "Edge.h"
#include "DijkstraUndirectedSP.h"

/**
 * @brief Construct a new GameWorld object
 */
GameWorld::GameWorld() {

    EdgeWeightedGraph g(8);

    g.addEdge( Edge( 4, 5, 0.35 ) );
    g.addEdge( Edge( 4, 7, 0.37 ) );
    g.addEdge( Edge( 5, 7, 0.28 ) );
    g.addEdge( Edge( 0, 7, 0.16 ) );
    g.addEdge( Edge( 1, 5, 0.32 ) );
    g.addEdge( Edge( 0, 4, 0.38 ) );
    g.addEdge( Edge( 2, 3, 0.17 ) );
    g.addEdge( Edge( 1, 7, 0.19 ) );
    g.addEdge( Edge( 0, 2, 0.26 ) );
    g.addEdge( Edge( 1, 2, 0.36 ) );
    g.addEdge( Edge( 1, 3, 0.29 ) );
    g.addEdge( Edge( 2, 7, 0.34 ) );
    g.addEdge( Edge( 6, 2, 0.40 ) );
    g.addEdge( Edge( 3, 6, 0.52 ) );
    g.addEdge( Edge( 6, 0, 0.58 ) );
    g.addEdge( Edge( 6, 4, 0.93 ) );
    //std::cout << g.toString() << "\n";

    int s = 6;
    DijkstraUndirectedSP d( g, s );

    for ( int i = 0; i < g.getV(); i++ ) {
        if ( d.hasPathTo( i ) ) {
            std::cout << std::format( "{} ate {} ({:.2f})  ", s, i, d.distToV(i) );
            std::stack<Edge> p = d.pathTo(i);
            while ( !p.empty() ) {
                std::cout << p.top().toString() << "  ";
                p.pop();
            }
            std::cout << "\n";
        } else {
            std::cout << std::format( "{} ate {} ({:.2f}) no path\n", s, i, d.distToV(i) );
        }
    }

};

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() = default;

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() {

    BeginDrawing();
    ClearBackground( WHITE );

    

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
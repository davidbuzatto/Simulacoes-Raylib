/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class declaration. This class should contain all
 * game components and its state.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include "Drawable.h"
#include "Loop.h"

class GameWorld : public virtual Drawable {

    Loop loop;
    float timeToNextAcum{0};
    float timeToNext;
    
public:

    /**
     * @brief Construct a new GameWorld object.
     */
    GameWorld();

    /**
     * @brief Destroy the GameWorld object.
     */
    virtual ~GameWorld();

    /**
     * @brief Reads user input and updates the state of the game.
     */
    void inputAndUpdate();

    /**
     * @brief Draws the state of the game.
     */
    void draw() override;

    /**
     * @brief Load game resources like images, textures, sounds, fonts, shaders,
     * etc. It will be called in Game Window after the creation of the Raylib
     * window.
     */
    static void loadResources();

    /**
     * @brief Unload the once loaded game resources. It will be called
     * after the game loop ends.
     */
    static void unloadResources();
    
};
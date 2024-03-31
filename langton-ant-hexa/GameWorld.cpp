/**
 * @file GameWorld.cpp
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld class implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <GameWorld.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <raylib.h>

#include <GameState.h>

/**
 * @brief Construct a new GameWorld object
 */
GameWorld::GameWorld() : 
        cellRadius( 16 ),
        boardWidth( 960 ),
        board( nullptr ),
        drawGrid( true ),
        timeToWait( 0.5 ),
        state( GameState::IDLE ),
        antMovesPerStep( 1 ),
        initialColor( ColorToInt( DARKGRAY ) ),
        showInfo( true ) {

    loadResources();
    std::cout << "creating game world..." << std::endl;
    
    updateBoard();
    
    //ant.setLine( 30 );
    //ant.setColumn( columns / 2 );
    /*generateAntDecisions( 
        std::vector<std::string>{ "L2", "N", "N", "L1", "L2", "L1" }, 
        0, 60, 1, 0.9, initialColor );*/

    /*generateAntDecisions( 
        std::vector<std::string>{ "L1", "L1", "R1", "R1" }, 
        315, 240, 1, 0.7, initialColor );*/

    /*generateAntDecisions( 
        std::vector<std::string>{ "L1", "L2", "N", "U", "L2", "L1", "R2" }, 
        180, 270, 1, 0.9, initialColor );*/

    generateAntDecisions( 
        std::vector<std::string>{ "R1", "R2", "N", "U", "R2", "R1", "L2" }, 
        60, 150, 1, 0.8, initialColor );

}

/**
 * @brief Destroy the GameWorld object
 */
GameWorld::~GameWorld() {
    unloadResources();
    std::cout << "destroying game world..." << std::endl;
    if ( board != nullptr ) {
        delete[] board;
    }
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void GameWorld::inputAndUpdate() {

    int mw = GetMouseWheelMove();
    if ( mw > 0 ) {
        cellRadius += 2;
        if ( cellRadius > MAX_CELL_RADIUS ) {
            cellRadius = MAX_CELL_RADIUS;
        }
        updateBoard();
    } else if ( mw < 0 ) {
        cellRadius -= 2;
        if ( cellRadius < MIN_CELL_RADIUS ) {
            cellRadius = MIN_CELL_RADIUS;
        }
        updateBoard();
    }

    if ( IsKeyDown( KEY_UP ) ) {
        timeToWait *= 2;
        if ( timeToWait > 2.0 ) {
            timeToWait = 2.0;
        }
    } else if ( IsKeyDown( KEY_DOWN ) ) {
        timeToWait /= 2;
        if ( timeToWait < 0.001 ) {
            timeToWait = 0.001;
        }
    }

    if ( IsKeyDown( KEY_RIGHT ) ) {
        antMovesPerStep += 10;        
    } else if ( IsKeyDown( KEY_LEFT ) ) {
        antMovesPerStep -= 10;
        if ( antMovesPerStep <= 0 ) {
            antMovesPerStep = 1;
        }
    }

    if ( state == GameState::RUNNING && currentTime >= timeToWait ) {
        nextStep();
        currentTime = 0;
    } else {
        currentTime += GetFrameTime();
    }

    if ( IsKeyPressed( KEY_R ) ) {
        std::fill_n( board, boardSize, initialColor );
        ant.setAngle( 120 );
        ant.setLine( lines / 2 );
        ant.setColumn( columns / 2 );
        ant.setMoving( false );
        currentMove = 0;
        state = GameState::IDLE;
    }

    if ( IsKeyPressed( KEY_SPACE ) ) {
        if ( state == GameState::IDLE ) {
            state = GameState::RUNNING;
            ant.setMoving( true );
        } else if ( state == GameState::RUNNING ) {
            state = GameState::PAUSED;
            ant.setMoving( false );
        } else if ( state == GameState::PAUSED ) {
            state = GameState::RUNNING;
            ant.setMoving( true );
        }
    }

    if ( IsKeyPressed( KEY_G ) ) {
        drawGrid = !drawGrid;
    }

    if ( IsKeyPressed( KEY_S ) ) {
        showInfo = !showInfo;
        ant.setDrawDecisionCycle( showInfo );
    }

}

/**
 * @brief Draws the state of the game.
 */
void GameWorld::draw() const {

    BeginDrawing();
    ClearBackground( GetColor( initialColor ) );

    for ( int i = 0; i < lines; i++ ) {
        for ( int j = 0; j <= columns; j++ ) {
            if ( board[i*columns + j] != initialColor ) {
                Vector2 v( j * (cellRadius + cellRadius2), i * 2 * cellApothema - ( j % 2 == 0 ? 0 : cellApothema ) );
                DrawPoly( v, 6, cellRadius, 0, GetColor( board[i*columns + j] ) );
            }
        }
    }

    if ( drawGrid ) {

        for ( int i = 0; i < lines; i++ ) {
            for ( int j = 0; j < columns; j++ ) {
                Vector2 v( j * (cellRadius + cellRadius2), i * 2 * cellApothema - ( j % 2 == 0 ? 0 : cellApothema ) );
                //DrawText( TextFormat( "%d, %d", i, j ), v.x, v.y, 10, BLACK );
                DrawPolyLines( v, 6, cellRadius, 0, BLACK );
            }
        }

    }

    ant.draw();

    if ( showInfo ) {
        DrawRectangle( 10, 10, 600, 75, Fade( WHITE, 0.8 ) );
        DrawRectangleLines( 10, 10, 600, 75, BLACK );
        DrawText( TextFormat( "%.3f segundo(s) para o próximo passo (impreciso).", timeToWait ), 20, 20, 20, BLUE );
        DrawText( TextFormat( "%d movimento(s) por passo.", antMovesPerStep ), 20, 40, 20, BLUE );
        DrawText( TextFormat( "movimento atual: %d", currentMove ), 20, 60, 20, BLUE );
    }

    EndDrawing();

}

int GameWorld::getBoardWidth() const {
    return boardWidth;
}

void GameWorld::nextStep() {
    for ( int i = 0; i < antMovesPerStep; i++ ) {
        if ( ant.isMoving() ) {
            currentMove++;
            ant.move( board, lines, columns );
        }
    }
}

void GameWorld::generateAntDecisions( 
    std::vector<std::string> turns, 
    int startHue, 
    int endHue, 
    float saturation, 
    float value, 
    unsigned int initialColor ) {
    
    unsigned int color;
    size_t steps = turns.size();
    int hueStep = abs( endHue - startHue ) / steps;

    if ( startHue > endHue ) {
        hueStep = -hueStep;
    }

    for ( size_t i = 0; i < steps; i++ ) {
        if ( i == 0 ) {
            color = initialColor;
        } else {
            color = ColorToInt( ColorFromHSV( startHue + (i-1) * hueStep, saturation, value ) );
        }
        std::string s = turns[i];
        if ( s == "N" ) {
            std::cout << "N" << std::endl;
            ant.addDecision( Decision( color, TURN_0 ) );
        } else if ( s == "R1" ) {
            std::cout << "R1" << std::endl;
            ant.addDecision( Decision( color, TURN_60 ) );
        } else if ( s == "R2" ) {
            std::cout << "R2" << std::endl;
            ant.addDecision( Decision( color, TURN_120 ) );
        } else if ( s == "U" ) {
            std::cout << "U" << std::endl;
            ant.addDecision( Decision( color, TURN_180 ) );
        } else if ( s == "L2" ) {
            std::cout << "L2" << std::endl;
            ant.addDecision( Decision( color, TURN_240 ) );
        } else if ( s == "L1" ) {
            std::cout << "L1" << std::endl;
            ant.addDecision( Decision( color, TURN_300 ) );
        }
    }

}

void GameWorld::updateBoard() {

    currentTime = 0;
    currentMove = 0;

    cellRadius2 = cellRadius/2;
    cellApothema = sqrt( cellRadius * cellRadius - cellRadius2 * cellRadius2 );

    lines = boardWidth / (cellApothema*2) + 2;
    columns = boardWidth / (cellRadius*1.5) + 2;

    ant.setAngle( 120 );
    ant.setCellRadius( cellRadius );
    ant.setCellApothema( cellApothema );
    ant.setLine( lines / 2 );
    ant.setColumn( columns / 2 );
    
    boardSize = columns * lines;
    if ( board != nullptr ) {
        delete[] board;
    }
    board = new unsigned int[boardSize];
    std::fill_n( board, boardSize, initialColor );

}

/**
 * @brief Load game resources like images, textures, sounds, fonts, shaders etc.
 * Should be called inside the constructor.
 */
void GameWorld::loadResources() {
    std::cout << "loading resources..." << std::endl;
}

/**
 * @brief Unload the once loaded game resources.
 * Should be called inside the destructor.
 */
void GameWorld::unloadResources() {
    std::cout << "unloading resources..." << std::endl;
}
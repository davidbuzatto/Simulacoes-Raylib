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
#include "Poligono.h"
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

    gw->quantidadePoligonos = 0;
    gw->quantidadeMaximaPoligonos = 50;
    gw->poligonos = (Poligono*) malloc( sizeof( Poligono ) * gw->quantidadeMaximaPoligonos );

    int matizInicial = 60;
    int matizFinal = 240;

    for ( int i = 0; i < gw->quantidadeMaximaPoligonos; i++ ) {
        adicionarPoligono( gw, (Poligono){
            .centro = { GetScreenWidth() / 2, GetScreenHeight() / 2 },
            .quantidadeLados = 5,
            .raio = ( 0.7 * ( GetScreenWidth() / 2 ) ) * ( 0.5f + 0.5f * ( (float) (i+1) ) / gw->quantidadeMaximaPoligonos),
            .angulo = 0,
            .larguraTraco = 5,
            .velocidadeAngular = (i+1) * 0.5f,
            .cor = ColorFromHSV( 
                matizInicial + (matizFinal - matizInicial) * ( (float) (i+1) ) / gw->quantidadeMaximaPoligonos,
                1, 1 )
        });
    }

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw->poligonos );
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();

    for ( int i = 0; i < gw->quantidadePoligonos; i++ ) {
        Poligono *p = &gw->poligonos[i];
        p->angulo += p->velocidadeAngular * delta;
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( BLACK );

    for ( int i = 0; i < gw->quantidadePoligonos; i++ ) {
        desenharPoligono( &gw->poligonos[i] );
    }

    EndDrawing();

}

void adicionarPoligono( GameWorld *gw, Poligono poligono ) {
    if ( gw->quantidadePoligonos < gw->quantidadeMaximaPoligonos ) {
        gw->poligonos[gw->quantidadePoligonos++] = poligono;
    }
}